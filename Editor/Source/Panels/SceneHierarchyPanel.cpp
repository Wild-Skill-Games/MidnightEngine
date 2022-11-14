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
		ImGuiIO& io = ImGui::GetIO();
		auto mediumFont = io.Fonts->Fonts[0];
		auto boldFont = io.Fonts->Fonts[1];

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

		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
		{
			values.x = resetValue;
		}
		ImGui::PopFont();

		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f);
		ImGui::PopItemWidth();

		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, { 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.0f, 1.0f, 0.0f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.0f, 0.5f, 0.0f, 1.0f });

		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
		{
			values.y = resetValue;
		}
		ImGui::PopFont();

		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f);
		ImGui::PopItemWidth();

		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, { 0.2f, 0.2f, 0.7f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.0f, 0.0f, 1.0f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.0f, 0.0f, 0.5f, 1.0f });

		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
		{
			values.z = resetValue;
		}
		ImGui::PopFont();

		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f);
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}

	template<typename T, typename UIFunction>
	static void DrawComponent(const std::string& name, Actor actor, UIFunction uiFunction, bool deleatable = true)
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

		if (actor.HasComponent<T>())
		{
			auto& component = actor.GetComponent<T>();
			auto contentRegionAvailable = ImGui::GetContentRegionAvail();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.0f, 4.0f));
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::Separator();

			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name.c_str());
			ImGui::PopStyleVar();

			ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5);
			if (ImGui::Button("+", ImVec2(lineHeight, lineHeight)))
			{
				ImGui::OpenPopup("Component settings");
			}


			bool removeComponent = false;
			if (ImGui::BeginPopup("Component settings"))
			{
				if (deleatable)
				{
					if (ImGui::MenuItem("Delete"))
					{
						removeComponent = true;
					}
				}
				ImGui::EndPopup();
			}

			if (open)
			{
				uiFunction(component);

				ImGui::TreePop();
			}

			if (removeComponent)
			{
				actor.RemoveComponent<T>();
			}
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

		ImGui::SameLine();
		ImGui::PushItemWidth(-1);


		if (ImGui::Button("Add Component"))
		{
			ImGui::OpenPopup("AddComponent");
		}

		if (ImGui::BeginPopup("AddComponent"))
		{
			if (!m_SelectionContext.HasComponent<Component::Camera>())
			{
				if (ImGui::MenuItem("Camera"))
				{
					m_SelectionContext.AddComponent<Component::Camera>();
					ImGui::CloseCurrentPopup();
				}
			}
			if (!m_SelectionContext.HasComponent<Component::SpriteRenderer>())
			{
				if (ImGui::MenuItem("Sprite Renderer"))
				{
					m_SelectionContext.AddComponent<Component::SpriteRenderer>();
					ImGui::CloseCurrentPopup();
				}
			}
			/*if (!m_SelectionContext.HasComponent<Component::NativeScript>())
			{
				if (ImGui::MenuItem("Native Script"))
				{
					m_SelectionContext.AddComponent<Component::NativeScript>();
					ImGui::CloseCurrentPopup();
				}
			}*/
			ImGui::EndPopup();
		}

		DrawComponent<Component::Transform>("Transform", actor, [](auto& component)
			{
				DrawVec3Control("Position", component.Position);
				DrawVec3Control("Rotation", component.Rotation);
				DrawVec3Control("Scale", component.Scale, 1.0f);
			}, false);

		DrawComponent<Component::SpriteRenderer>("Sprite Renderer", actor, [](auto& component)
			{
				ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));
			});

		DrawComponent<Component::Camera>("Camera", actor, [](auto& component)
			{
				auto& camera = component.SceneCamera;

				ImGui::Checkbox("Primary", &component.Primary);

				const char* projectionTypeString[] = { "Perspective", "Orthographic" };
				const char* currentProjectionTypeString = projectionTypeString[(int)camera.GetProjectionType()];

				if (ImGui::BeginCombo("Projection", currentProjectionTypeString))
				{
					for (int i = 0; i < 2; i++)
					{
						bool isSelected = currentProjectionTypeString == projectionTypeString[i];
						if (ImGui::Selectable(projectionTypeString[i], isSelected))
						{
							currentProjectionTypeString = projectionTypeString[i];
							camera.SetProjectionType((SceneCamera::ProjectionType)i);
						}

						if (isSelected)
						{
							ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::EndCombo();
				}

				if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
				{
					float verticalFOV = glm::degrees(camera.GetPerspectiveVerticalFOV());
					if (ImGui::DragFloat("Vertical FOV", &verticalFOV))
					{
						camera.SetPerspectiveVerticalFOV(glm::radians(verticalFOV));
					}

					float perspectiveNear = camera.GetPerspectiveNearClip();
					if (ImGui::DragFloat("Near", &perspectiveNear))
					{
						camera.SetPerspectiveNearClip(perspectiveNear);
					}

					float perspectiveFar = camera.GetPerspectiveFarClip();
					if (ImGui::DragFloat("Far", &perspectiveFar))
					{
						camera.SetPerspectiveFarClip(perspectiveFar);
					}
				}

				if (camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
				{
					float orthoSize = camera.GetOrthographicSize();
					if (ImGui::DragFloat("Size", &orthoSize))
					{
						camera.SetOrthographicSize(orthoSize);
					}

					float orthoNear = camera.GetOrthographicNearClip();
					if (ImGui::DragFloat("Near", &orthoNear))
					{
						camera.SetOrthographicNearClip(orthoNear);
					}

					float orthoFar = camera.GetOrthographicFarClip();
					if (ImGui::DragFloat("Far", &orthoFar))
					{
						camera.SetOrthographicFarClip(orthoFar);
					}

					ImGui::Checkbox("Fixed Aspect Ratio", &component.FixedAspectRatio);
				}
			});
	}
}