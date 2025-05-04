#include "Log.h"

namespace GameEngine {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		// https://github.com/gabime/spdlog/wiki/Custom-formatting
		spdlog::set_pattern("%^[%T] %n: %v%$");
		// Creating the consoles for the GameEngine and the client
		s_CoreLogger = spdlog::stdout_color_mt("GAME_ENGINE");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}