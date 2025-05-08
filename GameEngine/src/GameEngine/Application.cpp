#include "gepch.h"
#include "Application.h"

#include "GameEngine/Log.h"

namespace GameEngine {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Running = true;
	}

	Application::~Application() {}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}