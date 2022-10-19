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

		void OnUpdate(Timestep ts);

	private:
		entt::registry m_Registry;

		friend class Actor;
	};
}