#pragma once

#include "MidnightEngine.h"

namespace MidnightEngine
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;

	private:
		OrthographicCameraController m_CameraController;

		// Temporary
		Ref<VertexArray> m_VertexArray;
		Ref<Shader> m_Shader;
		Ref<Framebuffer> m_Framebuffer;

		Actor m_SquareEntity;

		Ref<Scene> m_ActiveScene;

		Ref<Texture2D> m_Texture2D;

		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;

		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

		glm::vec4 m_BackgroundColor = { 0.1f, 0.1f, 0.1f, 1.0f };

		struct Quad
		{
			Quad(glm::vec3 position = { 0.0f, 0.0f, 0.0f }, glm::vec2 size = { 1.0f, 1.0f }, bool useTexture = false, float tilingFactor = 1.0f, glm::vec4 tintColor = { 1.0f, 1.0f, 1.0f, 1.0f })
				: Position(position), Size(size), UseTexture(useTexture), TilingFactor(tilingFactor), TintColor(tintColor)
			{
			}

			glm::vec3 Position;
			glm::vec2 Size;
			bool UseTexture;
			float TilingFactor;
			glm::vec4 TintColor;
		};
		struct RotatedQuad : public Quad
		{
			RotatedQuad(glm::vec3 position = { 0.0f, 0.0f, 0.0f }, glm::vec2 size = { 1.0f, 1.0f }, float rotation = 0.0f, bool useTexture = false, float tilingFactor = 1.0f, glm::vec4 tintColor = { 1.0f, 1.0f, 1.0f, 1.0f })
				: Quad(position, size, useTexture, tilingFactor, tintColor), Rotation(rotation)
			{
			}

			float Rotation;
		};

		std::vector<Quad> m_Quads;
		std::vector<RotatedQuad> m_RotatedQuads;
	};
}