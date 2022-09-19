#pragma once

#ifdef ME_PLATFORM_WINDOWS

extern MidnightEngine::Application* MidnightEngine::CreateApplication();

int main(int arcc, char** argv)
{
	MidnightEngine::Log::Init();

	ME_PROFILE_BEGIN_SESSION("Startup", "MidnightEngineProfile-Startup.json");
	auto app = MidnightEngine::CreateApplication();
	ME_PROFILE_END_SESSION();

	ME_PROFILE_BEGIN_SESSION("Runtime", "MidnightEngineProfile-Runtime.json");
	app->Run();
	ME_PROFILE_END_SESSION();

	ME_PROFILE_BEGIN_SESSION("Shutdown", "MidnightEngineProfile-Shutdown.json");
	delete app;
	ME_PROFILE_END_SESSION();
}

#endif