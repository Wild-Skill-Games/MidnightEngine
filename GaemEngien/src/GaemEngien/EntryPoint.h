#pragma once

#ifdef PLATFORM_WINDOWS

extern GaemEngien::Application* GaemEngien::CreateApplication();

int main(int arcc, char** argv)
{
	GaemEngien::Log::Init();
	CORE_WARN("Core logger initialized");

	auto a = 5;

	GE_INFO("Client logger initialized, var={0}", a);

	auto app = GaemEngien::CreateApplication();
	app->Run();
	delete app;
}

#endif