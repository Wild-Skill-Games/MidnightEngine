#pragma once

#include "Core.h"

#include "Window.h"
#include "MidnightEngine/LayerStack.h"
#include "MidnightEngine/Events/Event.h"
#include "MidnightEngine/Events/ApplicationEvent.h"

#include "MidnightEngine/ImGui/ImGuiLayer.h"

#include "MidnightEngine/Renderer/Shader.h"
#include "MidnightEngine/Renderer/Buffer.h"

namespace MidnightEngine
{
	class MIDNIGHT_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event &e);

		void PushLayer(Layer *layer);
		void PushOverlay(Layer *layer);

		inline static Application &Get() { return *s_Instance; }
		inline Window &GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent &e);

	private:
		std::unique_ptr<Window> m_Window = nullptr;
		ImGuiLayer *m_ImGuiLayer;
		bool m_Runing = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;

		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;

	private:
		static Application *s_Instance;
	};

	// To be defined in client
	Application *CreateApplication();
}