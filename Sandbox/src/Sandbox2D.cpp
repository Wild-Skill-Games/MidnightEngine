#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(16.0f / 9.0f, true)
{
	{
		Quad quad;

		quad.Position = { -1.0f, 0.0f };
		quad.Size = { 0.8f, 0.8f };
		quad.Color = { 0.2f, 0.8f, 0.3f, 1.0f };

		m_Quads.push_back(quad);
	}

	{
		Quad quad;

		quad.Position = { 0.5f, -0.5f };
		quad.Size = { 0.5f, 0.75f };
		quad.Color = { 0.8f, 0.2f, 0.8f, 1.0f };

		m_Quads.push_back(quad);
	}

	{
		Quad quad;

		quad.Position = { 0.0f, 0.0f };
		quad.Size = { 2.0f, 1.0f };
		quad.Color = { 0.8f, 0.8f, 0.2f, 1.0f };

		m_Quads.push_back(quad);
	}
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

		MidnightEngine::Renderer2D::DrawQuad(m_Quads[0].Position, m_Quads[0].Size, m_Quads[0].Color);
		MidnightEngine::Renderer2D::DrawQuad(m_Quads[1].Position, m_Quads[1].Size, m_Quads[1].Color);
		MidnightEngine::Renderer2D::DrawQuad(m_Quads[2].Position, m_Quads[2].Size, m_Quads[2].Color);

		MidnightEngine::Renderer2D::EndScene();
	}
}
void Sandbox2D::OnImGuiRender()
{
	ME_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Background tint", glm::value_ptr(m_BackgroundColor));

	for (size_t i = 0; i < m_Quads.size(); i++)
	{
		ImGui::Separator();

		ImGui::PushID(i);

		ImGui::DragFloat2("Position", glm::value_ptr(m_Quads[i].Position), 0.1f);
		ImGui::DragFloat2("Size", glm::value_ptr(m_Quads[i].Size), 0.1f);
		ImGui::ColorEdit4("Color", glm::value_ptr(m_Quads[i].Color));

		ImGui::PopID();
	}

	ImGui::End();
}
void Sandbox2D::OnEvent(MidnightEngine::Event& event)
{
	m_CameraController.OnEvent(event);
}