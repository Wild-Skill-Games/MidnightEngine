#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


namespace GaemEngien
{
	class GAEMENGIEN_API Log
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
#define CORE_FATAL(...)::GaemEngien::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define CORE_ERROR(...)::GaemEngien::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_WARN(...)::GaemEngien::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_INFO(...)::GaemEngien::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_TRACE(...)::GaemEngien::Log::GetCoreLogger()->trace(__VA_ARGS__)

//Client log macros
#define GE_FATAL(...)::GaemEngien::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define GE_ERROR(...)::GaemEngien::Log::GetClientLogger()->error(__VA_ARGS__)
#define GE_WARN(...)::GaemEngien::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GE_INFO(...)::GaemEngien::Log::GetClientLogger()->info(__VA_ARGS__)
#define GE_TRACE(...)::GaemEngien::Log::GetClientLogger()->trace(__VA_ARGS__)