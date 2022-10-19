#include "mepch.h"
#include "Scene.h"

#include "Components.h"
#include <MidnightEngine/Renderer/Renderer2D.h>

#include <glm/glm.hpp>

#include "Actor.h"


namespace MidnightEngine
{
	static void DoMath(const glm::mat4& transform)
	{
	}

	Scene::Scene()
	{
		/*auto entity = m_Registry.create();

		m_Registry.emplace<Component::Transform>(entity, glm::mat4(1.0f));

		auto view = m_Registry.view<Component::Transform>();
		for (auto entity : view)
		{
			auto& transform = view.get<Component::Transform>(entity);
		}

		auto group = m_Registry.group<Component::Transform>(entt::get<Component::SpriteRenderer>);
		for (auto entity : group)
		{
			auto& [transform, mesh] = group.get<Component::Transform, Component::SpriteRenderer>(entity);
		}*/
	}
	Scene::~Scene()
	{

	}

	Actor Scene::CreateActor(const std::string& name)
	{
		auto actor = Actor(m_Registry.create(), this);
		actor.AddComponent<Component::Transform>();
		actor.AddComponent<Component::Tag>(name.empty() ? "Actor" : name);
		return actor;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		//render sprites
		Camera* mainCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;
		{
			auto group = m_Registry.view<Component::Transform, Component::Camera>();
			for (auto entity : group)
			{
				auto& [transform, camera] = group.get<Component::Transform, Component::Camera>(entity);
				if (camera.Primary)
				{
					mainCamera = &camera.CameraObject;
					cameraTransform = &transform.TransformMatrix;
					break;
				}
			}
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(mainCamera->GetProjection(), *cameraTransform);

			auto group = m_Registry.group<Component::Transform>(entt::get<Component::SpriteRenderer>);
			for (auto entity : group)
			{
				auto& [transform, sprite] = group.get<Component::Transform, Component::SpriteRenderer>(entity);
				Renderer2D::DrawRotatedQuad(transform, sprite.Color);
			}

			Renderer2D::EndScene();
		}
	}
}