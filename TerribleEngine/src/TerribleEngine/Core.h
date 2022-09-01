#pragma once

#ifdef TRBL_PLATFORM_WINDOWS
#ifdef BUILD_DLL
#define TERRIBLE_API __declspec(dllexport)
#else
#define TERRIBLE_API __declspec(dllimport)
#endif // BUILD_DLL
#else
#error TerribleEngine only supports Windows!
#endif // TERRIBLE_ENGINE_PLATFORM_WINDOWS

#if TERRIBLE_ENGINE_ENABLE_ASSERTS
#define TE_ASSERT(x, ...) { if(!(x)) { TE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define TERRIBLE_CORE_ASSERT(x, ...) { if(!(x)) { TERRIBLE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define TE_ASSERT(x, ...)
#define TERRIBLE_CORE_ASSERT(x, ...)
#endif // TERRIBLE_ENGINE_ENABLE_ASSERTS

#define BIT(x) (1 << x)