#pragma once

#include <memory>

#ifdef ME_PLATFORM_WINDOWS
#if ME_DYNAMIC_LINK
#ifdef ME_BUILD_DLL
#define MIDNIGHT_API __declspec(dllexport)
#else
#define MIDNIGHT_API __declspec(dllimport)
#endif // ME_BUILD_DLL
#else
#define MIDNIGHT_API
#endif // ME_DYNAMIC_LINK
#else
#error Midnight Engine only supports Windows!
#endif // ME_PLATFORM_WINDOWS

#ifdef ME_DEBUG
#define ME_ENABLE_ASSERTS
#endif // ME_DEBUG

#ifdef ME_ENABLE_ASSERTS
#define ME_ASSERT(x, ...) { if (!(x)) { ME_ERROR("Assertion Failed: {0}", __VA_ARGS__) ; __debugbreak() ; } }
#define ME_CORE_ASSERT(x, ...)  { if (!(x)) { ME_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak() ; } }
#else
#define ME_ASSERT(x, ...)
#define ME_CORE_ASSERT(x, ...)
#endif // ME_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define ME_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace MidnightEngine
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}