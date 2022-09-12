#pragma once

#include "MidnightEngine/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace MidnightEngine
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		~OpenGLContext();

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}