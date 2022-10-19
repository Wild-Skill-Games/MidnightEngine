#pragma once

#include <entt/entt.hpp>

#include "MidnightEngine/Core/Timestep.h"

#include "Components.h"

namespace MidnightEngine
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity(const std::string& name = std::string());

		//temporary, do not touch or it will explode
		entt::registry& Reg() { return m_Registry; }

		void OnUpdate(Timestep ts);

	private:
		entt::registry m_Registry;
	};
}