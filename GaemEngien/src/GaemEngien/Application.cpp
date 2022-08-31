#include "Application.h"

#include "GaemEngien/Events/ApplicationEvent.h"
#include "GaemEngien/Log.h"

namespace GaemEngien
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
			GE_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			GE_TRACE(e);
		}

		while (true);
	}
}