#pragma once

#include <glm/glm.hpp>

namespace MidnightEngine
{
	class Camera
	{
	public:
		Camera(const glm::mat4& projection);

		const glm::mat4& GetProjection() const { return m_Projection; }

		// TODO: implement the functions below
		void SetPerspective(float fov, float aspectRatio, float nearClip, float farClip);
		void SetOrthographic(float size, float aspectRatio, float nearClip, float farClip);

	private:
		glm::mat4 m_Projection;
	};
}