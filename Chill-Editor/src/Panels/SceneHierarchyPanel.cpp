#include "SceneHierarchyPanel.h"

#include <imgui/imgui.h>

#include "MidnightEngine/Scene/Components.h"

namespace MidnightEngine
{
	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context)
	{
		SetContext(context);
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene>& context)
	{
		m_Context = context;
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Hierarchy");

		m_Context->m_Registry.each([&](auto actorID)
			{
				Actor actor{ actorID, m_Context.get() };
				DrawActorNode(actor);
			});

		ImGui::End();
	}

	void SceneHierarchyPanel::DrawActorNode(Actor actor)
	{
		auto& tag = actor.GetComponent<Component::Tag>().TagString;
		ImGuiTreeNodeFlags flags = ((m_SelectionContext == actor) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)actor, flags, tag.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = actor;
		}

		bool entityDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
			{
				entityDeleted = true;
			}
			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGui::TreePop();
		}

		if (entityDeleted)
		{
			if (m_SelectionContext == actor)
			{
				m_SelectionContext = {};
			}
			actor.Destroy();
		}
	}
}