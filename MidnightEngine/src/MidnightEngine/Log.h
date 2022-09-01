#pragma once

#include "Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace MidnightEngine
{
	class MIDNIGHT_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core log macros
#define ME_CORE_FATAL(...)::MidnightEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define ME_CORE_ERROR(...)::MidnightEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ME_CORE_WARN(...)::MidnightEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ME_CORE_INFO(...)::MidnightEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ME_CORE_TRACE(...)::MidnightEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)

//Client log macros
#define ME_FATAL(...)::MidnightEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define ME_ERROR(...)::MidnightEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define ME_WARN(...)::MidnightEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ME_INFO(...)::MidnightEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define ME_TRACE(...)::MidnightEngine::Log::GetClientLogger()->trace(__VA_ARGS__)