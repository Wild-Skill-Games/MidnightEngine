#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Terrible
{
	class TERRIBLE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in client
	Application* CreateApplication();
}