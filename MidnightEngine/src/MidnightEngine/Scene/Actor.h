#pragma once

#include "Scene.h"
#include <entt/entt.hpp>

namespace MidnightEngine
{
	class Actor
	{
	public:
		Actor() = default;
		Actor(entt::entity handle, Scene* scene);
		Actor(const Actor& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			ME_CORE_ASSERT(!HasComponent<T>(), "Actor already has component!");

			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			ME_CORE_ASSERT(HasComponent<T>(), "Actor does not have component!");

			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.any_of<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			ME_CORE_ASSERT(HasComponent<T>(), "Actor does not have component!");

			return m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null && m_Scene; }

	private:
		entt::entity m_EntityHandle = entt::null;
		Scene* m_Scene = nullptr;
	};
}