#include "gepch.h"
#include "Core.h"
#include "Application.h"

#include "GameEngine/Log.h"

#include <GLFW/glfw3.h>

#include "Input.h"
#include "GameEngine/Renderer/Renderer.h"

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
			RenderCommand::SetClearColor({
				235.f / 255.f,
				24.f  / 255.f,
				106.f / 255.f,
				1.0f
			});
			RenderCommand::Clear();

			Renderer::BeginScene();

			// Update every layer before updating the window
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			Renderer::EndScene();

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
		RenderCommand::SetViewport({ 0, 0, e.GetWidth(), e.GetHeight() });
		return true;
	}
}