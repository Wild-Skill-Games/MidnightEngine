#pragma once

#include <glm/glm.hpp>

#include "SceneCamera.h"
#include "ScriptableActor.h"

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
			SceneCamera SceneCamera;
			bool Primary = true; // TODO : move to scene
			bool FixedAspectRatio = false;

			Camera() = default;
			Camera(const Camera&) = default;
		};

		struct NativeScript
		{
			ScriptableActor* Instance = nullptr;

			ScriptableActor* (*InstantiateScript)();
			void (*DestroyScript)(NativeScript*);

			template <typename T>
			void Bind()
			{
				InstantiateScript = []() { return static_cast<ScriptableActor*>(new T()); };
				DestroyScript = [](NativeScript* ns) { delete ns->Instance; ns->Instance = nullptr; };
			}
		};
	}
}