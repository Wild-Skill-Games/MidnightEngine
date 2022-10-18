#include "mepch.h"
#include "Scene.h"

#include <glm/glm.hpp>

namespace MidnightEngine
{
	static void DoMath(const glm::mat4& transform)
	{
	}

	static void OnTransformConstruct(entt::registry& registry, entt::entity entity)
	{
		auto& transform = registry.get<TransformComponent>(entity);
		DoMath(transform.Transform);
	}

	Scene::Scene()
	{
		struct MeshComponent {};
		struct TransformComponent
		{
			glm::mat4 Transform;

			TransformComponent() = default;
			TransformComponent(const TransformComponent&) = default;
			TransformComponent(const glm::mat4& transform)
				: Transform(transform)
			{
			}

			operator glm::mat4& () { return Transform; }
			operator const glm::mat4& () const { return Transform; }
		};

		auto entity = m_Registry.create();

		m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

		m_Registry.on_construct<TransformComponent>().connect<&OnTransformConstruct>();

		if (m_Registry.has<TransformComponent>(entity))
		{
			TransformComponent& transform = m_Registry.get<TransformComponent>(entity);
		}

		auto view = m_Registry.view<TransformComponent>();
		for (auto entity : view)
		{
			TransformComponent& transform = view.get<TransformComponent>(entity);
		}

		auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
		for (auto entity : group)
		{
			auto& [transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);

			Renderer::Submit(mesh, transform);
		}
	}
	Scene::~Scene()
	{

	}
}