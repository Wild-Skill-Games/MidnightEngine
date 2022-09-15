#include <MidnightEngine.h>
#include <Platform/OpenGL/OpenGLShader.h>

#include "mepch.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public MidnightEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		// Rendering T R Y E N G U L


		m_TriangleVertexArray.reset(MidnightEngine::VertexArray::Create());

		float triangleVertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.9f, 0.7f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.9f, 0.2f, 1.0f,
		};

		std::shared_ptr<MidnightEngine::VertexBuffer> triangleVertexBuffer;

		triangleVertexBuffer.reset(MidnightEngine::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));

		MidnightEngine::BufferLayout triangleLayout = {
			{MidnightEngine::ShaderDataType::Float3, "a_Position"},
			{MidnightEngine::ShaderDataType::Float4, "a_Color"},
		};

		triangleVertexBuffer->SetLayout(triangleLayout);
		m_TriangleVertexArray->AddVertexBuffer(triangleVertexBuffer);

		uint32_t triangleIndices[3] = { 0, 1, 2 };

		std::shared_ptr<MidnightEngine::IndexBuffer> triangleIndexBuffer;

		triangleIndexBuffer.reset(MidnightEngine::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));
		m_TriangleVertexArray->SetIndexBuffer(triangleIndexBuffer);

		std::string triangleVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string triangleFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		m_TriangleShader.reset(MidnightEngine::Shader::Create(triangleVertexSrc, triangleFragmentSrc));










		// Rendering S K U E R

		m_SquareVertexArray.reset(MidnightEngine::VertexArray::Create());

		float squareVertices[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};

		std::shared_ptr<MidnightEngine::VertexBuffer> squareVertexBuffer;

		squareVertexBuffer.reset(MidnightEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		MidnightEngine::BufferLayout squareLayout = {
			{MidnightEngine::ShaderDataType::Float3, "a_Position"},
		};

		squareVertexBuffer->SetLayout(squareLayout);
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		std::shared_ptr<MidnightEngine::IndexBuffer> squareIndexBuffer;

		squareIndexBuffer.reset(MidnightEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

		std::string sqaureVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string squareFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_SquareShader.reset(MidnightEngine::Shader::Create(sqaureVertexSrc, squareFragmentSrc));
	}

	void OnUpdate(MidnightEngine::Timestep ts) override
	{
		// Camera Movement


		if (MidnightEngine::Input::IsKeyPressed(ME_KEY_LEFT) || MidnightEngine::Input::IsKeyPressed(ME_KEY_A))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		}
		else if (MidnightEngine::Input::IsKeyPressed(ME_KEY_RIGHT) || MidnightEngine::Input::IsKeyPressed(ME_KEY_D))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		}

		if (MidnightEngine::Input::IsKeyPressed(ME_KEY_DOWN) || MidnightEngine::Input::IsKeyPressed(ME_KEY_S))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		}
		else if (MidnightEngine::Input::IsKeyPressed(ME_KEY_UP) || MidnightEngine::Input::IsKeyPressed(ME_KEY_W))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		}

		if (MidnightEngine::Input::IsKeyPressed(ME_KEY_Q))
		{
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}
		else if (MidnightEngine::Input::IsKeyPressed(ME_KEY_E))
		{
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}

		MidnightEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		MidnightEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		MidnightEngine::Renderer::BeginScene(m_Camera);

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);

		// TODO: Material system in the future

		//MidnightEngine::MaterialRef material = new MidnightEngine::Material(m_SquareShader);
		//MidnightEngine::MaterialInstanceRef mi = new MidnightEngine::MaterialInstance(m_SquareShader);

		//mi->SetValue("u_Color", redColor);
		//mi->SetTexture("u_Texture", texture);
		//mi->SetAlbedo("u_AlbedoMap", albedoMap);
		//squareMesh->SetMaterial(material);

		std::dynamic_pointer_cast<MidnightEngine::OpenGLShader>(m_SquareShader)->Bind();
		std::dynamic_pointer_cast<MidnightEngine::OpenGLShader>(m_SquareShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (size_t y = 0; y < 20; y++)
		{
			for (size_t x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11, 0.0);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				MidnightEngine::Renderer::Submit(m_SquareShader, m_SquareVertexArray, transform);
			}
		}

		MidnightEngine::Renderer::Submit(m_TriangleShader, m_TriangleVertexArray);

		MidnightEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(MidnightEngine::Event& event) override {}

private:
	std::shared_ptr<MidnightEngine::Shader> m_TriangleShader;
	std::shared_ptr<MidnightEngine::VertexArray> m_TriangleVertexArray;

	std::shared_ptr<MidnightEngine::Shader> m_SquareShader;
	std::shared_ptr<MidnightEngine::VertexArray> m_SquareVertexArray;

	MidnightEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 3.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 100.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
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