#pragma once

#include "MidnightEngine.h"

class Sandbox2D : public MidnightEngine::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(MidnightEngine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(MidnightEngine::Event& event) override;

private:
	MidnightEngine::OrthographicCameraController m_CameraController;

	MidnightEngine::Ref<MidnightEngine::VertexArray> m_VertexArray;
	MidnightEngine::Ref<MidnightEngine::Shader> m_Shader;

	MidnightEngine::Ref<MidnightEngine::Texture2D> m_Texture2D;

	glm::vec4 m_BackgroundColor = { 0.1f, 0.1f, 0.1f, 1.0f };

	struct Quad
	{
		glm::vec2 Position = { 0.0f, 0.0f };
		glm::vec2 Size = { 1.0f, 1.0f };
		glm::vec4 Color = { 1.0f, 1.0f, 1.0f, 1.0f };
	};

	std::vector<Quad> m_Quads;
};