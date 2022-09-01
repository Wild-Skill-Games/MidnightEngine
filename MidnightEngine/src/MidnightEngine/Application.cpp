#include "mepch.h"
#include "Application.h"

#include "MidnightEngine/Events/ApplicationEvent.h"
#include "MidnightEngine/Log.h"

#include <gl/GL.h>

namespace MidnightEngine
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
			//make the window magenta for debuging
			glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}