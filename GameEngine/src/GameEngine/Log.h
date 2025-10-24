#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h" // To log using ostream

namespace GameEngine {

	class Log
	{
	public:
		GE_API static void Init();

		// Search if it's safe to pass shared_ptr as reference instead of use make_shared
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		GE_API inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core Log Macros
#define GE_CORE_TRACE(...)    ::GameEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GE_CORE_INFO(...)     ::GameEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GE_CORE_WARN(...)     ::GameEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GE_CORE_ERROR(...)    ::GameEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GE_CORE_CRITICAL(...) ::GameEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log Macros
#define GE_TRACE(...)    ::GameEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GE_INFO(...)     ::GameEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define GE_WARN(...)     ::GameEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GE_ERROR(...)    ::GameEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define GE_CRITICAL(...) ::GameEngine::Log::GetClientLogger()->critical(__VA_ARGS__)