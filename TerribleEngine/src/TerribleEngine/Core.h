#pragma once

#ifdef TRBL_PLATFORM_WINDOWS
#ifdef TRBL_BUILD_DLL
#define TERRIBLE_API __declspec(dllexport)
#else
#define TERRIBLE_API __declspec(dllimport)
#endif // TRBL_BUILD_DLL
#else
#error TerribleEngine only supports Windows!
#endif // TRBL_PLATFORM_WINDOWS

#if TRBL_ENABLE_ASSERTS
#define TRBL_ASSERT(x, ...) { if(!(x)) { TRBL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define TRBL_CORE_ASSERT(x, ...) { if(!(x)) { TRBL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define TRBL_ASSERT(x, ...)
#define TRBL_CORE_ASSERT(x, ...)
#endif // TRBL_ENABLE_ASSERTS

#define BIT(x) (1 << x)