#pragma once

#ifdef PLATFORM_WINDOWS

#ifdef BUILD_DLL
#define	GAEMENGINE_API __declspec(dllexport)
#else
#define GAEMENGINE_API __declspec(dllimport)
#endif 
#else
#error GaemEngine only supports Windows!

#endif