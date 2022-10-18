#pragma once

#include <entt.hpp>

namespace MidnightEngine
{
	class Scene
	{
	public:
		Scene();
		~Scene();

	private:
		entt::registry m_Registry;
	};
}