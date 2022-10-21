#include "EditorLayer.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace MidnightEngine
{
	EditorLayer::EditorLayer()
		: Layer("Sandbox2D"), m_CameraController(16.0f / 9.0f, true)
	{
	}

	void EditorLayer::OnAttach()
	{
		ME_PROFILE_FUNCTION();

		m_Texture2D = Texture2D::Create("assets/textures/Image.png");

		FramebufferSpecification framebufferSpecification;
		framebufferSpecification.Width = 1280;
		framebufferSpecification.Height = 720;

		m_ViewportFramebuffer = Framebuffer::Create(framebufferSpecification);

		m_ActiveScene = CreateRef<Scene>();

		Actor actor = m_ActiveScene->CreateActor("Square1");
		actor.AddComponent<Component::SpriteRenderer>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

		actor = m_ActiveScene->CreateActor("Square2");
		actor.AddComponent<Component::SpriteRenderer>(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

		m_SquareActor = actor;

		m_CameraActor = m_ActiveScene->CreateActor("Camera A");
		m_CameraActor.GetComponent<Component::Transform>().Position.z = 10.0f;
		auto& cameraA = m_CameraActor.AddComponent<Component::Camera>().SceneCamera;
		cameraA.SetProjectionType(SceneCamera::ProjectionType::Perspective);

		m_SecondCameraActor = m_ActiveScene->CreateActor("Camera B");
		auto& cc = m_SecondCameraActor.AddComponent<Component::Camera>();
		cc.Primary = false;

		class CameraController : public ScriptableActor
		{
		public:
			float speed = 5.0f;

			void OnCreate()
			{
				auto& position = GetComponent<Component::Transform>().Position;
				position.x = rand() % 10 - 5.0f;
			}

			void OnUpdate(Timestep ts)
			{
				auto& position = GetComponent<Component::Transform>().Position;

				if (Input::IsKeyPressed(KeyCode::A))
				{
					position.x -= speed * ts;
				}
				if (Input::IsKeyPressed(KeyCode::D))
				{
					position.x += speed * ts;
				}
				if (Input::IsKeyPressed(KeyCode::W))
				{
					position.y += speed * ts;
				}
				if (Input::IsKeyPressed(KeyCode::S))
				{
					position.y -= speed * ts;
				}
			}
		};

		m_CameraActor.AddComponent<Component::NativeScript>().Bind<CameraController>();
		m_SecondCameraActor.AddComponent<Component::NativeScript>().Bind<CameraController>();

		m_SceneHierarchyPanel.SetContext(m_ActiveScene);
	}
	void EditorLayer::OnDetach()
	{
		ME_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		ME_PROFILE_FUNCTION();

		// Resize
		FramebufferSpecification spec = m_ViewportFramebuffer->GetSpecification();
		if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_ViewportFramebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);

			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}

		// Update
		if (m_ViewportFocused)
		{
			m_CameraController.OnUpdate(ts);
		}

		// Render
		Renderer2D::ResetStats();

		m_ViewportFramebuffer->Bind();
		RenderCommand::SetClearColor(m_BackgroundColor);
		RenderCommand::Clear();

		// Update Scene
		m_ActiveScene->OnUpdate(ts);

		m_ViewportFramebuffer->Unbind();
	}
	void EditorLayer::OnImGuiRender()
	{
		ME_PROFILE_FUNCTION();

		// If you strip some features of, this demo is pretty much equivalent to calling DockSpaceOverViewport()!
		// In most cases you should be able to just call DockSpaceOverViewport() and ignore all the code below!
		// In this specific demo, we are not using DockSpaceOverViewport() because:
		// - we allow the host window to be floating/moveable instead of filling the viewport (when opt_fullscreen == false)
		// - we allow the host window to have padding (when opt_padding == true)
		// - we have a local menu bar in the host window (vs. you could use BeginMainMenuBar() + DockSpaceOverViewport() in your code!)
		// TL;DR; this demo is more complicated than what you would normally use.
		// If we removed all the options we are showcasing, this demo would become:
		//     void ShowExampleAppDockSpace()
		//     {
		//         ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		//     }

		static bool dockspaceOpen = true;
		static bool opt_fullscreen = true;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				ImGui::MenuItem("Build Settings...");
				ImGui::MenuItem("Build And Run");

				ImGui::Separator();

				if (ImGui::MenuItem("Exit"))
				{
					Application::Get().Close();
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit"))
			{
				ImGui::MenuItem("Undo");
				ImGui::MenuItem("Redo");
				ImGui::MenuItem("Undo History");

				ImGui::Separator();

				ImGui::MenuItem("Select All");
				ImGui::MenuItem("Deselect All");
				ImGui::MenuItem("Select Children");
				ImGui::MenuItem("Select Prefab Root");
				ImGui::MenuItem("Invert Selection");

				ImGui::Separator();

				ImGui::MenuItem("Cut");
				ImGui::MenuItem("Copy");
				ImGui::MenuItem("Paste");
				ImGui::MenuItem("Paste As Child");

				ImGui::Separator();

				ImGui::MenuItem("Duplicate");
				ImGui::MenuItem("Rename");
				ImGui::MenuItem("Delete");

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Project"))
			{
				ImGui::MenuItem("New Project...");
				ImGui::MenuItem("Open Project...");
				ImGui::MenuItem("Save Project");

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Scene"))
			{
				ImGui::MenuItem("New Scene");
				ImGui::MenuItem("Open Scene");
				ImGui::MenuItem("Open Recent Scene");

				ImGui::Separator();

				ImGui::MenuItem("Save");
				ImGui::MenuItem("Save As...");
				ImGui::MenuItem("Save As Scene Template...");

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Object"))
			{
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Player"))
			{
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Tools"))
			{
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Window"))
			{
				ImGui::MenuItem("Panels");

				ImGui::Separator();

				ImGui::MenuItem("Next Window");
				ImGui::MenuItem("Previous Window");

				ImGui::Separator();

				ImGui::MenuItem("Layouts");

				ImGui::Separator();

				ImGui::MenuItem("Search");

				ImGui::Separator();

				ImGui::MenuItem("General");
				ImGui::MenuItem("Rendering");
				ImGui::MenuItem("Text");
				ImGui::MenuItem("Animation");
				ImGui::MenuItem("Audio");
				ImGui::MenuItem("Sequencing");
				ImGui::MenuItem("AI");
				ImGui::MenuItem("VisualEffects");
				ImGui::MenuItem("UI");

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Help"))
			{
				ImGui::MenuItem("About");
				ImGui::MenuItem("Documentation");

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Libary");
		ImGui::End();

		ImGui::Begin("Project");
		ImGui::End();

		ImGui::Begin("Game");
		ImGui::End();

		ImGui::Begin("Settings");

		ImGui::ColorEdit4("Background tint", glm::value_ptr(m_BackgroundColor));
		ImGui::Separator();

		ImGui::End();

		ImGui::Begin("Stats");

		auto stats = Renderer2D::GetStatistics();

		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Viewport");

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();

		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

		auto viewportPanelSize = ImGui::GetContentRegionAvail();

		if (m_ViewportSize != *((glm::vec2*)&viewportPanelSize) && viewportPanelSize.x > 0 && viewportPanelSize.y > 0)
		{
			m_ViewportFramebuffer->Resize(m_ViewportSize.x, m_ViewportSize.y);
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

			m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
		}

		auto viewportTextureID = m_ViewportFramebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)viewportTextureID, ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2(0, 1), ImVec2(1, 0));

		ImGui::PopStyleVar();
		ImGui::End();

		m_SceneHierarchyPanel.OnImGuiRender();

		ImGui::End();
	}
	void EditorLayer::OnEvent(Event& event)
	{
		m_CameraController.OnEvent(event);
	}
}