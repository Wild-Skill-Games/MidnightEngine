#pragma once

#include "Core.h"

#include "Window.h"
#include "MidnightEngine/LayerStack.h"
#include "MidnightEngine/Events/Event.h"
#include "MidnightEngine/Events/ApplicationEvent.h"

#include "MidnightEngine/Core/Timestep.h"

#include "MidnightEngine/ImGui/ImGuiLayer.h"

namespace MidnightEngine
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		Scope<Window> m_Window = nullptr;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Runing = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();
}