#pragma once

#include "MidnightEngine/Core/Core.h"
#include "MidnightEngine/Core/Log.h"
#include "MidnightEngine/Scene/Scene.h"
#include "MidnightEngine/Scene/Actor.h"

namespace MidnightEngine
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);

		void OnImGuiRender();

	private:
		void DrawActorNode(Actor actor);

	private:
		Ref<Scene> m_Context;
		Actor m_SelectionContext;
	};
}