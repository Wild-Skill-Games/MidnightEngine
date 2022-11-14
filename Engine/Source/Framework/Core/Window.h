#pragma once

#include "mepch.h"

#include "MidnightEngine/Core/Core.h"
#include "MidnightEngine/Events/Event.h"

namespace MidnightEngine
{
	struct WindowProperties
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProperties(const std::string& title = "Midnight Engine",
			uint32_t width = 1600,
			uint32_t height = 900)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	class MIDNIGHT_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProperties& properties = WindowProperties());
	};
};