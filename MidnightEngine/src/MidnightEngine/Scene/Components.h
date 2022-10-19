#pragma once

#include <glm/glm.hpp>

#include "MidnightEngine/Renderer/Camera.h"

namespace MidnightEngine
{
	namespace Component
	{
		struct Tag
		{
			std::string TagString;

			Tag() = default;
			Tag(const Tag&) = default;
			Tag(const std::string& tagString)
				: TagString(tagString)
			{
			}
		};

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

		struct Camera
		{
			MidnightEngine::Camera CameraObject;
			bool Primary = true; // TODO : move to scene

			Camera() = default;
			Camera(const Camera&) = default;
			Camera(const glm::mat4& projection)
				: CameraObject(projection)
			{
			}
		};
	}
}