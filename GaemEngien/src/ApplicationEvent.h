#pragma once

#include "Event.h"

#include <sstream>

namespace GaemEngien
{
	class GAEMENGIEN_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height)
		{

		}

		inline unsigned int GetWidth() const
		{
			return m_Width;
		}

		inline unsigned int GetHeight() const
		{
			return m_Height;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int m_Width, m_Height;
	};

	class GAEMENGIEN_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent()
		{

		}

		EVENT_CLASS_TYPE(EventType::WindowClose)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class GAEMENGIEN_API AppTickEvent : public Event
	{
	public:
		AppTickEvent()
		{

		}

		EVENT_CLASS_TYPE(AppTick)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class GAEMENGIEN_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent()
		{

		}

		EVENT_CLASS_TYPE(AppUpdate)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class GAEMENGIEN_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent()
		{

		}
		EVENT_CLASS_TYPE(AppRender)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}