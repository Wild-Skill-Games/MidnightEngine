#pragma once

#ifdef PLATFORM_WINDOWS

extern Terrible::Application* Terrible::CreateApplication();

int main(int arcc, char** argv)
{
	Terrible::Log::Init();
	TERRIBLE_CORE_WARN("Core logger initialized");

	auto a = 5;

	TE_INFO("Client logger initialized, var={0}", a);

	auto app = Terrible::CreateApplication();
	app->Run();
	delete app;
}

#endif