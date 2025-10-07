#pragma once

#ifdef GE_PLATFORM_WINDOWS

extern GameEngine::Application* GameEngine::CreateApplication();

int main(int argc, char** argv)
{
	GameEngine::Log::Init();

	auto app = GameEngine::CreateApplication();
	app->Run();
	delete app;
}

#else 
	#error Only Windows is supported!
#endif