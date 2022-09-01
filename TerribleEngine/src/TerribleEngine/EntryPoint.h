#pragma once

//#ifdef PLATFORM_WINDOWS

extern TerribleEngine::Application* TerribleEngine::CreateApplication();

int main(int arcc, char** argv)
{
	TerribleEngine::Log::Init();
	TRBL_CORE_WARN("Core logger initialized");

	auto a = 5;

	TRBL_INFO("Client logger initialized, var={0}", a);

	auto app = TerribleEngine::CreateApplication();
	app->Run();
	delete app;
}

//#endif