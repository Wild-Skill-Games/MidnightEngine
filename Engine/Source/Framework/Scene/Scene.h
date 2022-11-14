#pragma once

#include <entt/entt.hpp>

#include "MidnightEngine/Core/Timestep.h"

namespace MidnightEngine
{
	class Actor;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Actor CreateActor(const std::string& name = std::string());
		void DestroyActor(Actor actor);

		void OnUpdate(Timestep ts);
		void OnViewportResize(uint32_t width, uint32_t height);

	private:
		template <typename T>
		void OnComponentAdded(Actor actor, T& component);

	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth;
		uint32_t m_ViewportHeight;

		friend class Actor;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};
}