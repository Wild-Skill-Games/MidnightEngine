#pragma once

#ifdef PLATFORM_WINDOWS

#ifdef BUILD_DLL
#define GAEMENGIEN_API __declspec(dllexport)

#else
#define GAEMENGIEN_API __declspec(dllimport)

#endif
#else

#error GaemEngine only supports Windows!

#endif