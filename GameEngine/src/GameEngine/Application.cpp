#include "Application.h"

#include "GameEngine/Events/ApplicationEvent.h"
#include "GameEngine/Events/KeyEvent.h"
#include "GameEngine/Events/MouseEvent.h"
#include "GameEngine/Log.h"

namespace GameEngine {

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		// Window Events
		GE_WARN("Window Events");
		{
			WindowResizeEvent e(1280, 720);
			GE_TRACE(e.ToString());
			// Not working yet, spdlog has broken ostream support
			//GE_TRACE(e)
		}
		{
			WindowCloseEvent e;
			GE_TRACE(e.ToString());
		}

		// Key Events
		GE_WARN("Key Events");
		{
			KeyPressedEvent e(1, 10);
			GE_TRACE(e.ToString());
		}
		{
			KeyReleasedEvent e(1);
			GE_TRACE(e.ToString());
		}

		// Mouse Events
		GE_WARN("Mouse Events");
		{
			MouseMovedEvent e(100.5f, 200.2f);
			GE_TRACE(e.ToString());
		}
		{
			MouseScrolledEvent e(100.1f, 100.3f);
			GE_TRACE(e.ToString());
		}
		{
			MouseButtonPressedEvent e(1);
			GE_TRACE(e.ToString());
		}
		{
			MouseButtonReleasedEvent e(1);
			GE_TRACE(e.ToString());
		}
		GE_WARN("END OF ALL THE EVENTS");

		while (true);
	}
}