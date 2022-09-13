#include "mepch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace MidnightEngine
{
	void OpenGLRendererAPI::Init() {}
	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

	}
}