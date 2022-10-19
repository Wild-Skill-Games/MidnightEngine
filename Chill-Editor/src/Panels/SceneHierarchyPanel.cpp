#include "SceneHierarchyPanel.h"

#include <imgui/imgui.h>

#include "MidnightEngine/Scene/Components.h"
#include <glm/gtc/type_ptr.hpp>

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


		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
		{
			m_SelectionContext = {};
		}

		ImGui::End();


		ImGui::Begin("Inspector");
		if (m_SelectionContext)
		{
			DrawComponents(m_SelectionContext);
		}
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

	void SceneHierarchyPanel::DrawComponents(Actor actor)
	{
		if (actor.HasComponent<Component::Tag>())
		{
			auto& tag = actor.GetComponent<Component::Tag>().TagString;
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}

		if (actor.HasComponent<Component::Transform>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(Component::Transform).hash_code(), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth, "Transform"))
			{
				auto& transform = actor.GetComponent<Component::Transform>().TransformMatrix;

				ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);

				// Experimental, if u mess up w em, ull get some weird stuff
				ImGui::DragFloat3("transform[2]", glm::value_ptr(transform[2]), 0.1f);
				ImGui::DragFloat3("transform[1]", glm::value_ptr(transform[1]), 0.1f);
				ImGui::DragFloat3("transform[0]", glm::value_ptr(transform[0]), 0.1f);

				ImGui::TreePop();
			}
		}

		if (actor.HasComponent<Component::SpriteRenderer>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(Component::SpriteRenderer).hash_code(), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth, "Sprite Renderer"))
			{
				auto& spriteRenderer = actor.GetComponent<Component::SpriteRenderer>();

				ImGui::ColorEdit4("Color", glm::value_ptr(spriteRenderer.Color));

				ImGui::TreePop();
			}
		}

		if (actor.HasComponent<Component::Camera>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(Component::Camera).hash_code(), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth, "Camera"))
			{
				auto& camera = actor.GetComponent<Component::Camera>();

				const char* projectionTypeString[] = { "Perspective", "Orthographic" };
				const char* currentProjectionTypeString = projectionTypeString[(int)camera.SceneCamera.GetProjectionType()];

				ImGui::Checkbox("Primary", &camera.Primary);

				if (ImGui::BeginCombo("Projection", currentProjectionTypeString))
				{
					for (int i = 0; i < 2; i++)
					{
						bool isSelected = currentProjectionTypeString == projectionTypeString[i];
						if (ImGui::Selectable(projectionTypeString[i], isSelected))
						{
							currentProjectionTypeString = projectionTypeString[i];
							camera.SceneCamera.SetProjectionType((SceneCamera::ProjectionType)i);
						}

						if (isSelected)
						{
							ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::EndCombo();
				}

				if (camera.SceneCamera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
				{
					float verticalFOV = glm::degrees(camera.SceneCamera.GetPerspectiveVerticalFOV());
					if (ImGui::DragFloat("Vertical FOV", &verticalFOV))
					{
						camera.SceneCamera.SetPerspectiveVerticalFOV(glm::radians(verticalFOV));
					}

					float perspectiveNear = camera.SceneCamera.GetPerspectiveNearClip();
					if (ImGui::DragFloat("Near", &perspectiveNear))
					{
						camera.SceneCamera.SetPerspectiveNearClip(perspectiveNear);
					}

					float perspectiveFar = camera.SceneCamera.GetPerspectiveFarClip();
					if (ImGui::DragFloat("Far", &perspectiveFar))
					{
						camera.SceneCamera.SetPerspectiveFarClip(perspectiveFar);
					}
				}

				if (camera.SceneCamera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
				{
					float orthoSize = camera.SceneCamera.GetOrthographicSize();
					if (ImGui::DragFloat("Size", &orthoSize))
					{
						camera.SceneCamera.SetOrthographicSize(orthoSize);
					}

					float orthoNear = camera.SceneCamera.GetOrthographicNearClip();
					if (ImGui::DragFloat("Near", &orthoNear))
					{
						camera.SceneCamera.SetOrthographicNearClip(orthoNear);
					}

					float orthoFar = camera.SceneCamera.GetOrthographicFarClip();
					if (ImGui::DragFloat("Far", &orthoFar))
					{
						camera.SceneCamera.SetOrthographicFarClip(orthoFar);
					}

					ImGui::Checkbox("Fixed Aspect Ratio", &camera.FixedAspectRatio);
				}

				ImGui::TreePop();
			}
		}

		if (actor.HasComponent<Component::NativeScript>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(Component::NativeScript).hash_code(), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth, "Native Script"))
			{
				auto& nativeScript = actor.GetComponent<Component::NativeScript>();


				ImGui::TreePop();
			}
		}
	}
}