#include "mepch.h"
#include "SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace MidnightEngine
{
	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}

	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		m_OrthographicSize = size;
		m_OrthographicNear = nearClip;
		m_OrthographicFar = farClip;

		RecalculateProjection();
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		auto orthoLeft = -m_OrthographicSize * m_AspectRatio * 0.5f;
		auto orthoRight = m_OrthographicSize * m_AspectRatio * 0.5f;
		auto orthoBottom = -m_OrthographicSize * 0.5f;
		auto orthoTop = m_OrthographicSize * 0.5f;

		m_Projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, m_OrthographicNear, m_OrthographicFar);
	}
}