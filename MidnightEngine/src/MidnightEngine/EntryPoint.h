#pragma once

//#ifdef PLATFORM_WINDOWS

extern MidnightEngine::Application* MidnightEngine::CreateApplication();

int main(int arcc, char** argv)
{
	MidnightEngine::Log::Init();
	ME_CORE_WARN("Core logger initialized");

	auto a = 5;

	ME_INFO("Client logger initialized, var={0}", a);

	auto app = MidnightEngine::CreateApplication();
	app->Run();
	delete app;
}

//#endif