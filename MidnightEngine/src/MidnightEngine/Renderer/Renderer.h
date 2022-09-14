#pragma once

#include "RenderCommand.h"

namespace MidnightEngine
{
	class Renderer
	{
	public:
		static void BeginScene(class OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<class Shader>& shader, const std::shared_ptr<VertexArray> vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}