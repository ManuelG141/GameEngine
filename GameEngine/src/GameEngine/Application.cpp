#include "gepch.h"
#include "Core.h"
#include "Application.h"

#include "GameEngine/Log.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "Input.h"
#include "GameEngine/Renderer/Examples/ChessBoard.h"
#include "GameEngine/Renderer/Examples/Triangle.h"

namespace GameEngine {

	static GLenum ShaderType2GlType(const ShaderDataType& type)
	{
		switch (type)
		{
			case ShaderDataType::None:		return GL_NONE;
			case ShaderDataType::Float:		return GL_FLOAT;
			case ShaderDataType::Float2:	return GL_FLOAT;
			case ShaderDataType::Float3:	return GL_FLOAT;
			case ShaderDataType::Float4:	return GL_FLOAT;
			case ShaderDataType::Int:		return GL_INT;
			case ShaderDataType::Int2:		return GL_INT;
			case ShaderDataType::Int3:		return GL_INT;
			case ShaderDataType::Int4:		return GL_INT;
			case ShaderDataType::Mat3:		return GL_FLOAT;
			case ShaderDataType::Mat4:		return GL_FLOAT;
			case ShaderDataType::Bool:		return GL_BOOL;
		}

		GE_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return GL_NONE;
	}

	Application* Application::s_Instance = nullptr;

	Application::Application(const WindowProps& props)
	{
		GE_CORE_ASSERT(!s_Instance, "Application already exits!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create(props));
		m_Window->SetEventCallBack(GE_BIND_EVENT_FN(Application::OnEvent));

		// GameEngine Handles the ImGuiLayer now
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
		m_Running = true;

		// Draw a "ChessBoard" for testing
		// Vertex Array
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		// Create Vertex Buffer and bind it
		m_VertexBuffer.reset(VertexBuffer::Create(Triangle::vertices, sizeof(Triangle::vertices)));
		m_VertexBuffer->Bind();

		{ // Scope
			BufferLayout layout = { // This get destroyed after hitting the end of this scope
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color"}
			};

			m_VertexBuffer->SetLayout(layout);
		} // Scope

		unsigned int index = 0;
		for (const auto& element : m_VertexBuffer->GetLayout()) // possible setting iterator methods
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderType2GlType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				m_VertexBuffer->GetLayout().GetStride(),
				(void*)element.Offset
			);
			index++;
		}

		// Create Index buffer
		m_IndexBuffers["white"] = IndexBuffer::Create(Triangle::indices, Triangle::totalIndices);
		m_IndexBuffers["black"] = IndexBuffer::Create(Triangle::indices, Triangle::totalIndices);

		// Code using SubBuffers
		//glGenBuffers(1, &m_IndexBuffer);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		//
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Triangle::indices), Triangle::indices, GL_STATIC_DRAW);
		// Create a buffer to store all index data
		//glBufferData(
		//	GL_ELEMENT_ARRAY_BUFFER,
		//	sizeof(Triangle::indices) + sizeof(Triangle::blackIndices),
		//	0,
		//	GL_STATIC_DRAW
		//);
		//
		// Store the index data inside one buffer
		//glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(Triangle::indices), Triangle::indices); // from 0 to size of white indices
		//glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Triangle::indices), sizeof(Triangle::blackIndices), Triangle::blackIndices); // from end of white indices to black indices

		// Create Shader class to use it later
		m_Shaders["white"] = Shader::Create(Triangle::vertexSrc, Triangle::fragmentSrc);
		m_Shaders["black"] = Shader::Create(Triangle::vertexSrc, Triangle::fragmentSrc);
	}

	Application::~Application() {}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	// Not implemented yet
	void Application::PopLayer(Layer* layer) {}
	void Application::PopOverlay(Layer* overlay) {}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(GE_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(GE_BIND_EVENT_FN(Application::OnWindowResize));
		//GE_CORE_TRACE(e.ToString());

		// Send the event to all the layers and stop propagating it if some layer handles it
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.IsHandled())
				break;
		}
	}

	void Application::SetVSync(bool enabled)
	{
		m_Window->SetVSync(enabled);
	}


	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(m_VertexArray);
			// Draw "white" and "black" squares of the ChessBoard with the corresponding data and Shaders
			m_IndexBuffers["white"]->Bind();
			m_Shaders["white"]->Bind();
			glDrawElements(GL_TRIANGLES, m_IndexBuffers["white"]->GetCount(), GL_UNSIGNED_INT, nullptr); // Draw white indices
			
			m_IndexBuffers["black"]->Bind();
			m_Shaders["black"]->Bind();
			glDrawElements(GL_TRIANGLES, m_IndexBuffers["black"]->GetCount(), GL_UNSIGNED_INT, nullptr); // Draw white indices
			
			// Code with SubBuffers
			//m_Shaders["white"]->Bind();
			//glDrawElements(GL_TRIANGLES, ChessBoard::totalIndices, GL_UNSIGNED_INT, nullptr);
			//m_Shaders["black"]->Bind();
			//glDrawElements(GL_TRIANGLES, ChessBoard::totalIndices, GL_UNSIGNED_INT, (void*)sizeof(ChessBoard::whiteIndices)); // Draw black indices

			// Update every layer before updating the window
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
				
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		glViewport(0, 0, e.GetWidth(), e.GetHeight()); // Change the view port on window resize
		return true;
	}
}