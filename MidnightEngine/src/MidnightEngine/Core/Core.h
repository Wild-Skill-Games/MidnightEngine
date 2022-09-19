#pragma once

#include <memory>

// Platform detection using predefined macros

#ifdef _WIN32
#ifdef _WIN64
#define ME_PLATFORM_WINDOWS
#else // _WIN64
#error "x86 Builds are not supported!"
#endif // _WIN64
#elif defined(__APPLE__) || defined(__MACH__)
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR == 1
#error "IOS simulator is not supported!"
#elif TARGET_OS_IPHONE == 1
#define ME_PLATFORM_IOS
#error "IOS is not supported!"
#elif TARGET_OS_MAC == 1
#define ME_PLATFORM_MACOS
#error "MacOS is not supported!"
#else // TARGET_OS_MAC == 1
#error "Unknown Apple platform!"
#endif // TARGET_IPHONE_SIMULATOR == 1
#elif defined(__ANDROID__)
#define ME_PLATFORM_ANDROID
#error "Android is not supported!"
#elif defined(__linux__)
#define ME_PLATFORM_LINUX
#error "Linux is not supported!"
#else // defined(__linux__)
#error "Unknown platform!"
#endif // _WIN32

// DLL support

#ifdef ME_PLATFORM_WINDOWS
#if ME_DYNAMIC_LINK
#ifdef ME_BUILD_DLL
#define MIDNIGHT_API __declspec(dllexport)
#else // ME_BUILD_DLL
#define MIDNIGHT_API __declspec(dllimport)
#endif // ME_BUILD_DLL
#else // ME_PLATFORM_WINDOWS
#define MIDNIGHT_API
#endif // ME_DYNAMIC_LINK
#else
#error "MidnightEngine only supports Windows!"
#endif // ME_PLATFORM_WINDOWS

#ifdef ME_DEBUG
#define ME_ENABLE_ASSERTS
#endif // ME_DEBUG

#ifdef ME_ENABLE_ASSERTS
#define ME_ASSERT(x, ...) {	if (!(x)) { ME_ERROR("Assertion Failed: {0}", __VA_ARGS__);	__debugbreak();	} }
#define ME_CORE_ASSERT(x, ...) { if (!(x)) { ME_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }	}
#else
#define ME_ASSERT(x, ...)
#define ME_CORE_ASSERT(x, ...)
#endif // ME_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define ME_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace MidnightEngine
{
	template <typename T>
	using Scope = std::unique_ptr<T>;
	template <typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	using Ref = std::shared_ptr<T>;
	template <typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}