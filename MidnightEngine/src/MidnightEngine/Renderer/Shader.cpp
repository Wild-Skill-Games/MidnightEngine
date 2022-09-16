#include "mepch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace MidnightEngine
{

	Shader *Shader::Create(const std::string &filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ME_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(filepath);
		}

		ME_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Shader *Shader::Create(const std::string &vertexShader, const std::string &fragmentShader)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ME_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexShader, fragmentShader);
		}

		ME_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}