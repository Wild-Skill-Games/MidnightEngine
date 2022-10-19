#pragma once

#include <glm/glm.hpp>

namespace MidnightEngine
{
	namespace Component
	{
		struct Transform
		{
			glm::mat4 TransformMatrix = glm::mat4(1.0f);

			Transform() = default;
			Transform(const Transform&) = default;
			Transform(const glm::mat4& transformMatrix)
				: TransformMatrix(transformMatrix)
			{
			}

			operator glm::mat4& () { return TransformMatrix; }
			operator const glm::mat4& () const { return TransformMatrix; }
		};

		struct SpriteRenderer
		{
			glm::vec4 Color = { 1.0f, 1.0f, 1.0f, 1.0f };

			SpriteRenderer() = default;
			SpriteRenderer(const SpriteRenderer&) = default;
			SpriteRenderer(const glm::vec4& color)
				: Color(color)
			{
			}
		};
	}
}