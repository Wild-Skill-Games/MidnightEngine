#include "mepch.h"
#include "Camera.h"

namespace MidnightEngine
{
	Camera::Camera(const glm::mat4& projection)
		: m_Projection(projection)
	{
	}
}