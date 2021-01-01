#pragma once

#include "spdlog/spdlog.h"

#include <memory.h>

//SOURCE: https://github.com/gabime/spdlog

namespace Engine
{
	class Log
	{
	public:
		Log() = default;
		~Log() = default;

		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger()
		{
			return ms_EngineLogger;
		}
		inline static std::shared_ptr<spdlog::logger>& GetApplicationLogger()
		{
			return ms_ApplicationLogger;
		}
	private:
		static std::shared_ptr<spdlog::logger> ms_EngineLogger;
		static std::shared_ptr<spdlog::logger> ms_ApplicationLogger;

	};
}

// Core log macros
#define LOG_ENGINE_ERROR(...)	::Engine::Log::GetEngineLogger()->error(__VA_ARGS__)
#define LOG_ENGINE_WARN(...)	::Engine::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define LOG_ENGINE_INFO(...)	::Engine::Log::GetEngineLogger()->info(__VA_ARGS__)
#define LOG_ENGINE_TRACE(...)	::Engine::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define LOG_ENGINE_FATAL(...)	::Engine::Log::GetEngineLogger()->fatal(__VA_ARGS__)

// Core log macros
#define LOG_APP_ERROR(...)		::Engine::Log::GetApplicationLogger()->error(__VA_ARGS__)
#define LOG_APP_WARN(...)		::Engine::Log::GetApplicationLogger()->warn(__VA_ARGS__)
#define LOG_APP_INFO(...)		::Engine::Log::GetApplicationLogger()->info(__VA_ARGS__)
#define LOG_APP_TRACE(...)		::Engine::Log::GetApplicationLogger()->trace(__VA_ARGS__)
#define LOG_APP_FATAL(...)		::Engine::Log::GetApplicationLogger()->fatal(__VA_ARGS__)
