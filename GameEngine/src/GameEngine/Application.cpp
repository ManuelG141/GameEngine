#include "gepch.h"
#include "Core.h"
#include "Application.h"

#include "GameEngine/Log.h"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "Input.h"
#include "ChessBoard.h"

namespace GameEngine {

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

		// Vertex Buffer
		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		glBufferData(GL_ARRAY_BUFFER, sizeof(ChessBoard::vertices), ChessBoard::vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(ChessBoard::vertices[0]), nullptr);

		// Index Buffer
		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ChessBoard::whiteIndices), ChessBoard::whiteIndices, GL_STATIC_DRAW);
		// Create a buffer to store all index data
		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			sizeof(ChessBoard::whiteIndices) + sizeof(ChessBoard::blackIndices),
			0,
			GL_STATIC_DRAW
		);

		// Store the index data inside one buffer
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(ChessBoard::whiteIndices), ChessBoard::whiteIndices); // from 0 to size of white indices
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ChessBoard::whiteIndices), sizeof(ChessBoard::blackIndices), ChessBoard::blackIndices); // from end of white indices to black indices
		
		m_Shaders["whiteSqr"] = new Shader(ChessBoard::vertexSrc, ChessBoard::whiteFragmentSrc);
		m_Shaders["blackSqr"] = new Shader(ChessBoard::vertexSrc, ChessBoard::blackFragmentSrc);
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
			m_Shaders["whiteSqr"]->Bind();
			glDrawElements(GL_TRIANGLES, ChessBoard::totalIndices, GL_UNSIGNED_INT, nullptr); // Draw white indices
			m_Shaders["blackSqr"]->Bind();
			glDrawElements(GL_TRIANGLES, ChessBoard::totalIndices, GL_UNSIGNED_INT, (void*)sizeof(ChessBoard::whiteIndices)); // Draw black indices

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