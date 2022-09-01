#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace MidnightEngine
{
	class MIDNIGHT_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window> m_Window = nullptr;
		bool m_Runing = true;
	};

	//To be defined in client
	Application* CreateApplication();
}