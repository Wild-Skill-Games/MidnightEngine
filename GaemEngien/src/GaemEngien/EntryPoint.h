#pragma once

#ifdef PLATFORM_WINDOWS

extern GaemEngien::Application* GaemEngien::CreateApplication();

int main(int arcc, char** argv)
{
	auto app = GaemEngien::CreateApplication();
	app->Run();
	delete app;
}

#endif