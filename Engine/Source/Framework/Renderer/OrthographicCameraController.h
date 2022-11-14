#pragma once

#include "MidnightEngine/Renderer/OrthographicCamera.h"
#include "MidnightEngine/Core/Timestep.h"

#include "MidnightEngine/Events/ApplicationEvent.h"
#include "MidnightEngine/Events/MouseEvent.h"

namespace MidnightEngine
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void SetProjection(float left, float right, float bottom, float top);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void OnResize(float width, float height);

		OrthographicCamera& GetCamera() { return m_CameraController; }
		const OrthographicCamera& GetCamera() const { return m_CameraController; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_CameraController;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};
}