#pragma once

#include "Core.h"

#include <spdlog/spdlog.h>

namespace TerribleEngine
{
	class TERRIBLE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()
		{
			return s_CoreLogger;
		}

		inline static std::shared_ptr<spdlog::logger>& GetClientLogger()
		{
			return s_ClientLogger;
		}

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core log macros
#define TERRIBLE_CORE_FATAL(...)::TerribleEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define TERRIBLE_CORE_ERROR(...)::TerribleEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TERRIBLE_CORE_WARN(...)::TerribleEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TERRIBLE_CORE_INFO(...)::TerribleEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TERRIBLE_CORE_TRACE(...)::TerribleEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)

//Client log macros
#define TE_FATAL(...)::TerribleEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define TE_ERROR(...)::TerribleEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define TE_WARN(...)::TerribleEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TE_INFO(...)::TerribleEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define TE_TRACE(...)::TerribleEngine::Log::GetClientLogger()->trace(__VA_ARGS__)