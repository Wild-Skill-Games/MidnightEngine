#include "trblpch.h"
#include "Application.h"

#include "TerribleEngine/Events/ApplicationEvent.h"
#include "TerribleEngine/Log.h"

namespace TerribleEngine
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {}

	void Application::Run()
	{
		while (m_Runing)
		{
			m_Window->OnUpdate();
		}
	}
}