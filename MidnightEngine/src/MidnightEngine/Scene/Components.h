#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
			//glm::mat4 TransformMatrix = glm::mat4(1.0f);
			glm::vec3 Position = glm::vec3(0.0f);
			glm::vec3 Rotation = glm::vec3(0.0f);
			glm::vec3 Scale = glm::vec3(1.0f);

			Transform() = default;
			Transform(const Transform&) = default;
			Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
				: Position(position), Rotation(rotation), Scale(scale)
			{
			}

			glm::mat4& GetTransform()
			{
				auto rotation = glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.x), glm::vec3(1, 0, 0))
					* glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.y), glm::vec3(0, 1, 0))
					* glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.z), glm::vec3(0, 0, 1));

				return glm::translate(glm::mat4(1.0f), Position) *
					rotation *
					glm::scale(glm::mat4(1.0f), Scale);
			}
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