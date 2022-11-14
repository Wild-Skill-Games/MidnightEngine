#include "mepch.h"
#include "Actor.h"

namespace MidnightEngine
{
	Actor::Actor(entt::entity handle, Scene* scene)
		:m_EntityHandle(handle), m_Scene(scene)
	{
	}
}