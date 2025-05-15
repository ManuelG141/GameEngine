#include "gepch.h"
#include "Core.h"
#include "Application.h"

#include "GameEngine/Log.h"

#include "GLFW/glfw3.h"

namespace GameEngine {

	Application* Application::s_Instance = nullptr;

	Application::Application(const WindowProps& props)
	{
		GE_CORE_ASSERT(!s_Instance, "Application already exits!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create(props));
		m_Window->SetEventCallBack(GE_BIND_EVENT_FN(Application::OnEvent));
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

		GE_CORE_TRACE(e.ToString());

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
			glClearColor(0.5, 0.5, 0.5, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			// Update every layer before updating the window
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}