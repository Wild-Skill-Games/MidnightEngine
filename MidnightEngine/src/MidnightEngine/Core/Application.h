#pragma once

#include "MidnightEngine/Core/Core.h"

#include "MidnightEngine/Core/Window.h"
#include "MidnightEngine/Core/LayerStack.h"
#include "MidnightEngine/Events/Event.h"
#include "MidnightEngine/Events/ApplicationEvent.h"

#include "MidnightEngine/Core/Timestep.h"

#include "MidnightEngine/ImGui/ImGuiLayer.h"

namespace MidnightEngine
{
	class Application
	{
	public:
		Application(const std::string& name = "MidnightEngine");
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void Run();
		inline Window& GetWindow() { return *m_Window; }

		void Close();

		inline ImGuiLayer* GetImGuiLayer() { return  m_ImGuiLayer; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		Scope<Window> m_Window = nullptr;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Runing = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();
}