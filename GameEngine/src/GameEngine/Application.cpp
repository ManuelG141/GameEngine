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

		// Draw a ChessBoard & Triangle for testing
		// 1. Chess Board 
		// Vertex Array
		m_VertexArrays["chess"].reset(VertexArray::Create());

		// Create Vertex Buffer and bind it
		std::shared_ptr<VertexBuffer> ChessBoardVB(VertexBuffer::Create(ChessBoard::vertices, sizeof(ChessBoard::vertices)));
		ChessBoardVB->Bind();

		// Set layout for VertexBuffer
		ChessBoardVB->SetLayout({
			{ShaderDataType::Float3, "a_Position"}
		});
		// Add VertexBuffer to the VertexArray
		m_VertexArrays["chess"]->AddVertexBuffer("board", ChessBoardVB);

		// Create Index buffer
		std::shared_ptr<IndexBuffer> ChessBoardWhiteIndicesIB(IndexBuffer::Create(ChessBoard::whiteIndices, ChessBoard::totalIndices));
		std::shared_ptr<IndexBuffer> ChessBoardBlackIndicesIB(IndexBuffer::Create(ChessBoard::blackIndices, ChessBoard::totalIndices));
		m_VertexArrays["chess"]->AddIndexBuffer("white", ChessBoardWhiteIndicesIB);
		m_VertexArrays["chess"]->AddIndexBuffer("black", ChessBoardBlackIndicesIB);

		// Create Shader class to use it later
		m_Shaders["white"].reset(Shader::Create(ChessBoard::vertexSrc, ChessBoard::whiteFragmentSrc));
		m_Shaders["black"].reset(Shader::Create(ChessBoard::vertexSrc, ChessBoard::blackFragmentSrc));
		
		m_VertexArrays["chess"]->UnBind();

		// 2. Triangle
		m_VertexArrays["triangle"].reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> TriangleVB(VertexBuffer::Create(Triangle::vertices, sizeof(Triangle::vertices)));
		TriangleVB->Bind();

		TriangleVB->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"}
		});
		m_VertexArrays["triangle"]->AddVertexBuffer("vertices+color", TriangleVB);

		std::shared_ptr<IndexBuffer> TriangleIB(IndexBuffer::Create(Triangle::indices, Triangle::totalIndices));
		m_VertexArrays["triangle"]->AddIndexBuffer("indices", TriangleIB);

		m_Shaders["triangle"].reset(Shader::Create(Triangle::vertexSrc, Triangle::fragmentSrc));
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

			// ChessBoard
			m_VertexArrays["chess"]->Bind();
			// Draw "white" and "black" squares of the ChessBoard with the corresponding data and Shaders
			m_VertexArrays["chess"]->GetIndexBuffer("white")->Bind();
			m_VertexArrays["chess"]->GetVertexBuffer("board");
			m_Shaders["white"]->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArrays["chess"]->GetIndexBuffer("white")->GetCount(), GL_UNSIGNED_INT, nullptr); // Draw white indices
			
			m_VertexArrays["chess"]->GetIndexBuffer("black")->Bind();
			m_Shaders["black"]->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArrays["chess"]->GetIndexBuffer("black")->GetCount(), GL_UNSIGNED_INT, nullptr); // Draw black indices
			
			// Triangle
			m_VertexArrays["triangle"]->Bind();
			m_VertexArrays["triangle"]->GetIndexBuffer("indices")->Bind();
			m_Shaders["triangle"]->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArrays["triangle"]->GetIndexBuffer("indices")->GetCount(), GL_UNSIGNED_INT, nullptr);

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