#include "trblpch.h"
#include "Application.h"

#include "TerribleEngine/Events/ApplicationEvent.h"
#include "TerribleEngine/Log.h"

namespace Terrible
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			TE_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			TE_TRACE(e);
		}

		while (true);
	}
}