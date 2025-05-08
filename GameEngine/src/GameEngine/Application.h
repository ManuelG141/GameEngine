#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace GameEngine {

	// dllexport is required to use this class in sandbox application
	class GE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running;
	};

	// To be defined in the client
	Application* CreateApplication();

}