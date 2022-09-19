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
	m_Texture2D = MidnightEngine::Texture2D::Create("assets/textures/Image.png");
}
void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(MidnightEngine::Timestep ts)
{ // Update
	m_CameraController.OnUpdate(ts);

	// Render
	MidnightEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	MidnightEngine::RenderCommand::Clear();

	MidnightEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());

	MidnightEngine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.2f, 0.8f, 0.3f, 1.0f });
	MidnightEngine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.8f, 0.3f, 0.8f, 1.0f });
	MidnightEngine::Renderer2D::DrawQuad({ 0.5f, 0.7f }, { 0.7f, 0.4f }, { 0.8f, 0.8f, 0.2f, 1.0f });
	MidnightEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_Texture2D, 10.0f, glm::vec4(1.0f));

	MidnightEngine::Renderer2D::EndScene();

	// TODO: add these functions Shader::SetMat4, Shader::SetFloat4
	//std::dynamic_pointer_cast<MidnightEngine::OpenGLShader>(m_Shader)->Bind();
	//std::dynamic_pointer_cast<MidnightEngine::OpenGLShader>(m_Shader)->UploadUniformFloat4("u_Color", m_Color);
}
void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_Color));
	ImGui::End();
}
void Sandbox2D::OnEvent(MidnightEngine::Event& event)
{
	m_CameraController.OnEvent(event);
}