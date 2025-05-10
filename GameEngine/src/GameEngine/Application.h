#pragma once

#include "Core.h"
#include "Window.h"
#include "GameEngine/LayerStack.h"
#include "GameEngine/Events/Event.h"
#include "GameEngine/Events/ApplicationEvent.h"

namespace GameEngine {

	// dllexport is required to use this class in sandbox application
	class GE_API Application
	{
	public:
		Application(const WindowProps& props = WindowProps());
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		void SetVSync(bool enabled);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running;
		LayerStack m_LayerStack;
	};

	// To be defined in the client
	Application* CreateApplication();

}