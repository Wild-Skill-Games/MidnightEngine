#pragma once

#include "RenderCommand.h"

namespace MidnightEngine
{
	class Renderer
	{
	public:
		static void BeginScene(class OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<class Shader>& shader, const std::shared_ptr<VertexArray> vertexArray, const glm::mat4 transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}