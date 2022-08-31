#pragma once

//#ifdef PLATFORM_WINDOWS

extern TerribleEngine::Application* TerribleEngine::CreateApplication();

int main(int arcc, char** argv)
{
	TerribleEngine::Log::Init();
	TERRIBLE_CORE_WARN("Core logger initialized");

	auto a = 5;

	TE_INFO("Client logger initialized, var={0}", a);

	auto app = TerribleEngine::CreateApplication();
	app->Run();
	delete app;
}

//#endif