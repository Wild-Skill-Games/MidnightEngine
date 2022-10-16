#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

EditorLayer::EditorLayer()
	: Layer("Sandbox2D"), m_CameraController(16.0f / 9.0f, true)
{
}

void EditorLayer::OnAttach()
{
	ME_PROFILE_FUNCTION();

	m_Texture2D = MidnightEngine::Texture2D::Create("assets/textures/Image.png");
}
void EditorLayer::OnDetach()
{
	ME_PROFILE_FUNCTION();
}

void EditorLayer::OnUpdate(MidnightEngine::Timestep ts)
{
	ME_PROFILE_FUNCTION();

	m_CameraController.OnUpdate(ts);

	// Render
	MidnightEngine::Renderer2D::ResetStats();
	{
		ME_PROFILE_SCOPE("RenderCommand Render");
		MidnightEngine::RenderCommand::SetClearColor(m_BackgroundColor);
		MidnightEngine::RenderCommand::Clear();
	}

	{
		ME_PROFILE_SCOPE("Renderer2D Draw");
		MidnightEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());

		for (auto& quad : m_Quads)
		{
			if (quad.UseTexture)
			{
				MidnightEngine::Renderer2D::DrawQuad(quad.Position, quad.Size, m_Texture2D, quad.TilingFactor, quad.TintColor);
			}
			else
			{
				MidnightEngine::Renderer2D::DrawQuad(quad.Position, quad.Size, quad.TintColor);
			}
		}

		for (auto& quad : m_RotatedQuads)
		{
			if (quad.UseTexture)
			{
				MidnightEngine::Renderer2D::DrawRotatedQuad(quad.Position, quad.Size, quad.Rotation, m_Texture2D, quad.TilingFactor, quad.TintColor);
			}
			else
			{
				MidnightEngine::Renderer2D::DrawRotatedQuad(quad.Position, quad.Size, quad.Rotation, quad.TintColor);
			}
		}

		MidnightEngine::Renderer2D::EndScene();
	}
}
void EditorLayer::OnImGuiRender()
{
	ME_PROFILE_FUNCTION();

	ImGui::Begin("Inspector");

	auto stats = MidnightEngine::Renderer2D::GetStatistics();

	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Background tint", glm::value_ptr(m_BackgroundColor));
	ImGui::Separator();

	ImGui::Text("Quads: %d", m_Quads.size());
	ImGui::Separator();

	for (auto i = 0; i < m_Quads.size(); i++)
	{
		ImGui::PushID(i);
		ImGui::Text("Quad %d", i);
		ImGui::DragFloat3("Position", glm::value_ptr(m_Quads[i].Position), 0.1f);
		ImGui::DragFloat2("Size", glm::value_ptr(m_Quads[i].Size), 0.1f);
		ImGui::Checkbox("Use Texture", &m_Quads[i].UseTexture);
		ImGui::DragFloat("Tiling Factor", &m_Quads[i].TilingFactor, 0.1f, 0.0f, 10.0f);
		ImGui::ColorEdit4("Color", glm::value_ptr(m_Quads[i].TintColor));
		ImGui::Separator();
		ImGui::PopID();
	}

	if (ImGui::Button("Create Quad"))
	{
		m_Quads.push_back(Quad());
	}
	ImGui::Separator();

	ImGui::Text("Rotated Quads: %d", m_RotatedQuads.size());
	ImGui::Separator();

	for (auto i = 0; i < m_RotatedQuads.size(); i++)
	{
		ImGui::PushID(m_Quads.size() + i);
		ImGui::Text("Rotated Quad %d", i);
		ImGui::DragFloat3("Position", glm::value_ptr(m_RotatedQuads[i].Position), 0.1f);
		ImGui::DragFloat2("Size", glm::value_ptr(m_RotatedQuads[i].Size), 0.1f);
		ImGui::DragFloat("Rotation", &m_RotatedQuads[i].Rotation, 0.1f);
		ImGui::Checkbox("Use Texture", &m_RotatedQuads[i].UseTexture);
		ImGui::DragFloat("Tiling Factor", &m_RotatedQuads[i].TilingFactor, 0.1f, 0.0f, 10.0f);
		ImGui::ColorEdit4("Color", glm::value_ptr(m_RotatedQuads[i].TintColor));
		ImGui::Separator();
		ImGui::PopID();
	}

	if (ImGui::Button("Create Rotated Quad"))
	{
		m_RotatedQuads.push_back(RotatedQuad());
	}

	ImGui::End();
}
void EditorLayer::OnEvent(MidnightEngine::Event& event)
{
	m_CameraController.OnEvent(event);
}