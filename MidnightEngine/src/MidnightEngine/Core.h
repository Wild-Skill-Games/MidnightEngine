#pragma once

#ifdef ME_PLATFORM_WINDOWS
#ifdef ME_BUILD_DLL
#define MIDNIGHT_API __declspec(dllexport)
#else
#define MIDNIGHT_API __declspec(dllimport)
#endif // ME_BUILD_DLL
#else
#error Midnight Engine only supports Windows!
#endif // ME_PLATFORM_WINDOWS

#if ME_ENABLE_ASSERTS
#define ME_ASSERT(x, ...) { if(!(x)) { ME_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define ME_CORE_ASSERT(x, ...) { if(!(x)) { ME_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define ME_ASSERT(x, ...)
#define ME_CORE_ASSERT(x, ...)
#endif // ME_ENABLE_ASSERTS

#define BIT(x) (1 << x)