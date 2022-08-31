#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


namespace Terrible
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
#define TERRIBLE_CORE_FATAL(...)::Terrible::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define TERRIBLE_CORE_ERROR(...)::Terrible::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TERRIBLE_CORE_WARN(...)::Terrible::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TERRIBLE_CORE_INFO(...)::Terrible::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TERRIBLE_CORE_TRACE(...)::Terrible::Log::GetCoreLogger()->trace(__VA_ARGS__)

//Client log macros
#define TE_FATAL(...)::Terrible::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define TE_ERROR(...)::Terrible::Log::GetClientLogger()->error(__VA_ARGS__)
#define TE_WARN(...)::Terrible::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TE_INFO(...)::Terrible::Log::GetClientLogger()->info(__VA_ARGS__)
#define TE_TRACE(...)::Terrible::Log::GetClientLogger()->trace(__VA_ARGS__)