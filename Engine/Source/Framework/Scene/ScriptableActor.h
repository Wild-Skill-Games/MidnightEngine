#pragma once

#include "Actor.h"

namespace MidnightEngine
{
	class ScriptableActor
	{
	public:
		virtual ~ScriptableActor() {}

		template<typename T>
		T& GetComponent()
		{
			return m_Actor.GetComponent<T>();
		}

	protected:
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(Timestep ts) {}

	private:
		Actor m_Actor;
		friend class Scene;
	};
}