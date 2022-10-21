#include "SceneHierarchyPanel.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

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

		if (ImGui::BeginPopupContextWindow(0, 1, false))
		{
			if (ImGui::MenuItem("Create Empty Actor"))
			{
				m_Context->CreateActor("Empty Actor");
			}

			ImGui::EndPopup();
		}

		ImGui::End();


		ImGui::Begin("Inspector");
		if (m_SelectionContext)
		{
			DrawComponents(m_SelectionContext);

			if (ImGui::Button("Add Component"))
			{
				ImGui::OpenPopup("AddComponent");
			}

			if (ImGui::BeginPopup("AddComponent"))
			{
				if (ImGui::MenuItem("Camera"))
				{
					m_SelectionContext.AddComponent<Component::Camera>();
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::MenuItem("Sprite Renderer"))
				{
					m_SelectionContext.AddComponent<Component::SpriteRenderer>();
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::MenuItem("Native Script"))
				{
					//m_SelectionContext.AddComponent<Component::NativeScript>();
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
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

		bool actorDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Actor"))
			{
				actorDeleted = true;
			}
			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGui::TreePop();
		}

		if (actorDeleted)
		{
			if (m_SelectionContext == actor)
			{
				m_SelectionContext = {};
			}
			//actor.Destroy();
			m_Context->DestroyActor(actor);
		}
	}

	static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());

		ImGui::NextColumn();
		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });

		auto lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;

		auto buttonSize = ImVec2(lineHeight + 3.0f, lineHeight);

		ImGui::PushStyleColor(ImGuiCol_Button, { 0.7f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 1.0f, 0.0f, 0.0f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.5f, 0.0f, 0.0f, 1.0f });

		if (ImGui::Button("X", buttonSize))
		{
			values.x = resetValue;
		}

		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f);
		ImGui::PopItemWidth();

		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, { 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.0f, 1.0f, 0.0f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.0f, 0.5f, 0.0f, 1.0f });
		if (ImGui::Button("Y", buttonSize))
		{
			values.y = resetValue;
		}
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f);
		ImGui::PopItemWidth();

		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, { 0.2f, 0.2f, 0.7f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.0f, 0.0f, 1.0f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.0f, 0.0f, 0.5f, 1.0f });
		if (ImGui::Button("Z", buttonSize))
		{
			values.z = resetValue;
		}
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f);
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
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
				auto& transform = actor.GetComponent<Component::Transform>();

				DrawVec3Control("Position", transform.Position);
				DrawVec3Control("Rotation", transform.Rotation);
				DrawVec3Control("Scale", transform.Scale, 1.0f);

				ImGui::TreePop();
			}
		}

		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth;

		if (actor.HasComponent<Component::SpriteRenderer>())
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.0f, 4.0f));

			bool open = ImGui::TreeNodeEx((void*)typeid(Component::SpriteRenderer).hash_code(), treeNodeFlags, "Sprite Renderer");
			ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);

			if (ImGui::Button("+", ImVec2(20.0f, 20.0f)))
			{
				ImGui::OpenPopup("Component settings");
			}
			ImGui::PopStyleVar();

			bool removeComponent = false;
			if (ImGui::BeginPopup("Component settings"))
			{
				if (ImGui::MenuItem("Delete"))
				{
					removeComponent = true;
				}
				ImGui::EndPopup();
			}

			if (open)
			{
				auto& spriteRenderer = actor.GetComponent<Component::SpriteRenderer>();

				ImGui::ColorEdit4("Color", glm::value_ptr(spriteRenderer.Color));

				ImGui::TreePop();
			}

			if (removeComponent)
			{
				actor.RemoveComponent<Component::SpriteRenderer>();
			}
		}

		if (actor.HasComponent<Component::Camera>())
		{
			bool open = ImGui::TreeNodeEx((void*)typeid(Component::Camera).hash_code(), treeNodeFlags, "Camera");

			ImGui::SameLine();
			if (ImGui::Button("+"))
			{
				ImGui::OpenPopup("Component settings");
			}

			bool removeComponent = false;
			if (ImGui::BeginPopup("Component settings"))
			{
				if (ImGui::MenuItem("Delete"))
				{
					removeComponent = true;
				}
				ImGui::EndPopup();
			}

			if (open)
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

			if (removeComponent)
			{
				actor.RemoveComponent<Component::Camera>();
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