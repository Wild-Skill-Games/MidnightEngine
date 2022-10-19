#pragma once

#include "MidnightEngine.h"
#include "Panels/SceneHierarchyPanel.h"

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
		Ref<Framebuffer> m_ViewportFramebuffer;

		Ref<Scene> m_ActiveScene;
		Actor m_SquareActor;

		bool m_PrimaryCamera = true;

		Actor m_CameraActor;
		Actor m_SecondCameraActor;

		Ref<Texture2D> m_Texture2D;

		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;

		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

		glm::vec4 m_BackgroundColor = { 0.1f, 0.1f, 0.1f, 1.0f };

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
	};
}