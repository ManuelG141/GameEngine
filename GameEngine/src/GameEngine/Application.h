#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "GameEngine/Events/ApplicationEvent.h"

namespace GameEngine {

	// dllexport is required to use this class in sandbox application
	class GE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running;
	};

	// To be defined in the client
	Application* CreateApplication();

}