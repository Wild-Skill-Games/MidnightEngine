#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "MidnightEngine/Events/ApplicationEvent.h"

namespace MidnightEngine
{
	class MIDNIGHT_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window = nullptr;
		bool m_Runing = true;
		LayerStack m_LayerStack;
	};

	//To be defined in client
	Application* CreateApplication();
}