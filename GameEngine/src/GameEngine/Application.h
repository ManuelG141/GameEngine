#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace GameEngine {

	// dllexport is required to use this class in sandbox application
	class GE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in the client
	Application* CreateApplication();

}