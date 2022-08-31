#pragma once

#ifdef TERRIBLE_ENGINE_PLATFORM_WINDOWS

#ifdef BUILD_DLL
#define TERRIBLE_API __declspec(dllexport)

#else
#define TERRIBLE_API __declspec(dllimport)

#endif
#else

#error TerribleEngine only supports Windows!

#endif

#define BIT(x) (1 << x)