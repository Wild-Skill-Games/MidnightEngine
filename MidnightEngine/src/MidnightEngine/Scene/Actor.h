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

			T& component = m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
			//m_Scene->OnComponentAdded(T::GetID());
			m_Scene->OnComponentAdded<T>(*this, component);
			return component;
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

			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		void Destroy()
		{
			m_Scene->DestroyActor(*this);
		}

		operator bool() const { return m_EntityHandle != entt::null && m_Scene; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }
		operator entt::entity() const { return m_EntityHandle; }

		bool operator ==(const Actor& other) const { return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene; }

		bool operator !=(const Actor& other) const { return !(*this == other); }
	private:
		entt::entity m_EntityHandle = entt::null;
		Scene* m_Scene = nullptr;
	};
}