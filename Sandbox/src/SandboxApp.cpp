#include <MidnightEngine.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public MidnightEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(16.0f / 9.0f, true)
	{
		// Rendering T R Y E N G U L

		m_TriangleVertexArray.reset(MidnightEngine::VertexArray::Create());

		float triangleVertices[3 * 7] = {
			-0.5f,
			-0.5f,
			0.0f,
			0.9f,
			0.7f,
			1.0f,
			1.0f,
			0.5f,
			-0.5f,
			0.0f,
			0.5f,
			0.0f,
			1.0f,
			1.0f,
			0.0f,
			0.5f,
			0.0f,
			0.0f,
			0.9f,
			0.2f,
			1.0f,
		};

		MidnightEngine::Ref<MidnightEngine::VertexBuffer> triangleVertexBuffer;

		triangleVertexBuffer.reset(MidnightEngine::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));

		MidnightEngine::BufferLayout triangleLayout = {
			{MidnightEngine::ShaderDataType::Float3, "a_Position"},
			{MidnightEngine::ShaderDataType::Float4, "a_Color"},
		};

		triangleVertexBuffer->SetLayout(triangleLayout);
		m_TriangleVertexArray->AddVertexBuffer(triangleVertexBuffer);

		uint32_t triangleIndices[3] = { 0, 1, 2 };

		MidnightEngine::Ref<MidnightEngine::IndexBuffer> triangleIndexBuffer;

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

		m_TriangleShader = MidnightEngine::Shader::Create("TRYENGUL", triangleVertexSrc, triangleFragmentSrc);

		// Rendering S K U E R

		m_SquareVertexArray.reset(MidnightEngine::VertexArray::Create());

		float squareVertices[4 * 5] = {
			-0.5f,
			-0.5f,
			0.0f,
			0.0f,
			0.0f,
			0.5f,
			-0.5f,
			0.0f,
			1.0f,
			0.0f,
			0.5f,
			0.5f,
			0.0f,
			1.0f,
			1.0f,
			-0.5f,
			0.5f,
			0.0f,
			0.0f,
			1.0f,
		};

		MidnightEngine::Ref<MidnightEngine::VertexBuffer> squareVertexBuffer;

		squareVertexBuffer.reset(MidnightEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		MidnightEngine::BufferLayout squareLayout = {
			{MidnightEngine::ShaderDataType::Float3, "a_Position"},
			{MidnightEngine::ShaderDataType::Float2, "a_TextureCoordonate"},
		};

		squareVertexBuffer->SetLayout(squareLayout);
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		MidnightEngine::Ref<MidnightEngine::IndexBuffer> squareIndexBuffer;

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

		m_SquareShader = MidnightEngine::Shader::Create("SKUER", sqaureVertexSrc, squareFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture2D = MidnightEngine::Texture2D::Create("assets/textures/Image.png");
		m_LogoTexture = MidnightEngine::Texture2D::Create("assets/textures/Logo.png");

		std::dynamic_pointer_cast<MidnightEngine::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<MidnightEngine::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(MidnightEngine::Timestep ts) override
	{
		// Update
		m_CameraController.OnUpdate(ts);

		// Render
		MidnightEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		MidnightEngine::RenderCommand::Clear();

		MidnightEngine::Renderer::BeginScene(m_CameraController.GetCamera());

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);

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

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture2D->Bind();
		MidnightEngine::Renderer::Submit(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_LogoTexture->Bind();
		MidnightEngine::Renderer::Submit(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Rendering T R Y E N G U L
		// MidnightEngine::Renderer::Submit(m_TriangleShader, m_TriangleVertexArray);

		MidnightEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(MidnightEngine::Event& event) override
	{
		m_CameraController.OnEvent(event);
	}

private:
	MidnightEngine::ShaderLibrary m_ShaderLibrary;

	MidnightEngine::Ref<MidnightEngine::Shader> m_TriangleShader;
	MidnightEngine::Ref<MidnightEngine::VertexArray> m_TriangleVertexArray;

	MidnightEngine::Ref<MidnightEngine::Shader> m_SquareShader;
	MidnightEngine::Ref<MidnightEngine::VertexArray> m_SquareVertexArray;

	MidnightEngine::Ref<MidnightEngine::Texture2D> m_Texture2D, m_LogoTexture;

	MidnightEngine::OrthographicCameraController m_CameraController;

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