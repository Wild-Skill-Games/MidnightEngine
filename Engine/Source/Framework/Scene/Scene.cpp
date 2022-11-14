#include "mepch.h"
#include "Scene.h"

#include "Components.h"
#include <MidnightEngine/Renderer/Renderer2D.h>

#include <glm/glm.hpp>

#include "Actor.h"


namespace MidnightEngine
{
	Scene::Scene()
	{
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

	void Scene::DestroyActor(Actor actor)
	{
		m_Registry.destroy(actor);
	}

	void Scene::OnUpdate(Timestep ts)
	{
		// update scripts
		{
			m_Registry.view<Component::NativeScript>().each([=](auto actor, auto& ns)
				{
					// TODO : move to Scene:OnScenePlay
					if (!ns.Instance)
					{
						ns.Instance = ns.InstantiateScript();
						ns.Instance->m_Actor = Actor{ actor, this };
						ns.Instance->OnCreate();
					}

					ns.Instance->OnUpdate(ts);
				});
		}

		//render sprites
		Camera* mainCamera = nullptr;
		glm::mat4 cameraTransform;
		{
			auto view = m_Registry.view<Component::Transform, Component::Camera>();
			for (auto entity : view)
			{
				auto [transform, camera] = view.get<Component::Transform, Component::Camera>(entity);
				if (camera.Primary)
				{
					mainCamera = &camera.SceneCamera;
					cameraTransform = transform.GetTransform();
					break;
				}
			}
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(mainCamera->GetProjection(), cameraTransform);

			auto group = m_Registry.group<Component::Transform>(entt::get<Component::SpriteRenderer>);
			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<Component::Transform, Component::SpriteRenderer>(entity);
				Renderer2D::DrawRotatedQuad(transform.GetTransform(), sprite.Color);
			}

			Renderer2D::EndScene();
		}
	}
	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		auto view = m_Registry.view<Component::Camera>();
		for (auto entity : view)
		{
			auto& camera = view.get<Component::Camera>(entity);
			if (!camera.FixedAspectRatio)
			{
				camera.SceneCamera.SetViewportSize(width, height);
			}
		}
	}

	template <typename T>
	void Scene::OnComponentAdded(Actor actor, T& component)
	{
		static_assert(false);
	}

	template <>
	void Scene::OnComponentAdded<Component::Transform>(Actor actor, Component::Transform& component)
	{
	}

	template <>
	void Scene::OnComponentAdded<Component::Camera>(Actor actor, Component::Camera& component)
	{
		component.SceneCamera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}

	template <>
	void Scene::OnComponentAdded<Component::SpriteRenderer>(Actor actor, Component::SpriteRenderer& component)
	{
	}

	template <>
	void Scene::OnComponentAdded<Component::Tag>(Actor actor, Component::Tag& component)
	{
	}

	template <>
	void Scene::OnComponentAdded<Component::NativeScript>(Actor actor, Component::NativeScript& component)
	{
	}
}