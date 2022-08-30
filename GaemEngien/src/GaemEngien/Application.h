#pragma once

#include "Core.h"

namespace GaemEngien
{
	class GAEMENGIEN_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in client
	Application* CreateApplication();
}