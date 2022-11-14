#include "mepch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace MidnightEngine
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		ME_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		ME_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ME_CORE_ASSERT(status, "Failed to initialize Glad!");

		ME_CORE_INFO("OpenGL Info:");
		ME_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		ME_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		ME_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

#ifdef ME_ENABLE_ASSERTS
		int versionMajor, versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		ME_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "MidnightEngine requires at least OpenGL version 4.5!");
#endif // ME_ENABLE_ASSERTS

	}

	void OpenGLContext::SwapBuffers()
	{
		ME_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}