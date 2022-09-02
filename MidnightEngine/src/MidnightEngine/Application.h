#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "MidnightEngine/Events/ApplicationEvent.h"

#include "Window.h"


namespace MidnightEngine
{
	class MIDNIGHT_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window = nullptr;
		bool m_Runing = true;
	};

	//To be defined in client
	Application* CreateApplication();
}