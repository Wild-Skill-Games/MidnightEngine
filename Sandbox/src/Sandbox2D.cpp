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

		MidnightEngine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.5f }, m_Texture2D, 1.0, { 0.8f, 0.2f, 0.8f, 1.0f });
		MidnightEngine::Renderer2D::DrawQuad({ -0.5f, 0.5f }, { 1.0f, 1.0f }, m_Texture2D, 1.0, { 0.8f, 0.8f, 0.2f, 1.0f });
		MidnightEngine::Renderer2D::DrawQuad({ 0.5f, 0.5f }, { 0.75f, 0.75f }, m_Texture2D, 1.0, { 0.8f, 0.8f, 0.2f, 1.0f });
		MidnightEngine::Renderer2D::DrawQuad({ -0.5f, -0.5f }, { 0.75f, 0.75f }, { 0.8f, 0.8f, 0.2f, 1.0f });

		MidnightEngine::Renderer2D::EndScene();
	}
}
void Sandbox2D::OnImGuiRender()
{
	ME_PROFILE_FUNCTION();

	/*ImGui::Begin("Settings");
	ImGui::ColorEdit4("Background tint", glm::value_ptr(m_BackgroundColor));

	ImGui::End();*/
}
void Sandbox2D::OnEvent(MidnightEngine::Event& event)
{
	m_CameraController.OnEvent(event);
}