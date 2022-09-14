#include <MidnightEngine.h>

#include "imgui/imgui.h"

class ExampleLayer : public MidnightEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(MidnightEngine::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.9f, 0.7f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.9f, 0.2f, 1.0f,
		};

		std::shared_ptr<MidnightEngine::VertexBuffer> vertexBuffer;

		vertexBuffer.reset(MidnightEngine::VertexBuffer::Create(vertices, sizeof(vertices)));

		MidnightEngine::BufferLayout layout = {
			{MidnightEngine::ShaderDataType::Float3, "a_Position"},
			{MidnightEngine::ShaderDataType::Float4, "a_Color"},
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };

		std::shared_ptr<MidnightEngine::IndexBuffer> indexBuffer;

		indexBuffer.reset(MidnightEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(new MidnightEngine::Shader(vertexSrc, fragmentSrc));
	}

	void OnUpdate() override
	{
		// Camera Movement

		if (MidnightEngine::Input::IsKeyPressed(ME_KEY_LEFT) || MidnightEngine::Input::IsKeyPressed(ME_KEY_A))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed;
		}
		else if (MidnightEngine::Input::IsKeyPressed(ME_KEY_RIGHT) || MidnightEngine::Input::IsKeyPressed(ME_KEY_D))
		{
			m_CameraPosition.x += m_CameraMoveSpeed;
		}

		if (MidnightEngine::Input::IsKeyPressed(ME_KEY_DOWN) || MidnightEngine::Input::IsKeyPressed(ME_KEY_S))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed;
		}
		else if (MidnightEngine::Input::IsKeyPressed(ME_KEY_UP) || MidnightEngine::Input::IsKeyPressed(ME_KEY_W))
		{
			m_CameraPosition.y += m_CameraMoveSpeed;
		}

		if (MidnightEngine::Input::IsKeyPressed(ME_KEY_Q))
		{
			m_CameraRotation -= m_CameraRotationSpeed;
		}
		else if (MidnightEngine::Input::IsKeyPressed(ME_KEY_E))
		{
			m_CameraRotation += m_CameraRotationSpeed;
		}





		MidnightEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		MidnightEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		MidnightEngine::Renderer::BeginScene(m_Camera);

		MidnightEngine::Renderer::Submit(m_Shader, m_VertexArray);

		MidnightEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {}

	void OnEvent(MidnightEngine::Event& event) override {}

private:
	std::shared_ptr<MidnightEngine::Shader> m_Shader;
	std::shared_ptr<MidnightEngine::VertexArray> m_VertexArray;

	MidnightEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.03f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 2.0f;
};

class Sandbox : public MidnightEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {}
};

MidnightEngine::Application* MidnightEngine::CreateApplication()
{
	return new Sandbox();
}