#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(16.0f / 9.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	ME_PROFILE_FUNCTION();

	m_Texture2D = MidnightEngine::Texture2D::Create("assets/textures/Image.png");
}
void Sandbox2D::OnDetach()
{
	ME_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(MidnightEngine::Timestep ts)
{
	ME_PROFILE_FUNCTION();

	m_CameraController.OnUpdate(ts);

	// Render
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
			MidnightEngine::Renderer2D::DrawQuad(quad.Position, quad.Size, quad.TintColor);
		}

		for (auto& quad : m_RotatedQuads)
		{
			MidnightEngine::Renderer2D::DrawRotatedQuad(quad.Position, quad.Size, quad.Rotation, quad.TintColor);
		}

		MidnightEngine::Renderer2D::EndScene();
	}
}
void Sandbox2D::OnImGuiRender()
{
	ME_PROFILE_FUNCTION();

	ImGui::Begin("Inspector");
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
		ImGui::ColorEdit4("Color", glm::value_ptr(m_Quads[i].TintColor));
		ImGui::Separator();
		ImGui::PopID();
	}

	if (ImGui::Button("Create Quad"))
	{
		m_Quads.push_back({ { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f } });
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
		ImGui::ColorEdit4("Color", glm::value_ptr(m_RotatedQuads[i].TintColor));
		ImGui::Separator();
		ImGui::PopID();
	}

	if (ImGui::Button("Create Rotated Quad"))
	{
		m_RotatedQuads.push_back({ { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, 0.0f, { 0.8f, 0.2f, 0.3f, 1.0f } });
	}

	ImGui::End();
}
void Sandbox2D::OnEvent(MidnightEngine::Event& event)
{
	m_CameraController.OnEvent(event);
}