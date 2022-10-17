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

		m_Framebuffer = Framebuffer::Create(framebufferSpecification);
	}
	void EditorLayer::OnDetach()
	{
		ME_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		ME_PROFILE_FUNCTION();

		m_CameraController.OnUpdate(ts);

		// Render
		Renderer2D::ResetStats();
		{
			ME_PROFILE_SCOPE("RenderCommand Render");
			m_Framebuffer->Bind();
			RenderCommand::SetClearColor(m_BackgroundColor);
			RenderCommand::Clear();
		}

		{
			ME_PROFILE_SCOPE("Renderer2D Draw");
			Renderer2D::BeginScene(m_CameraController.GetCamera());

			for (auto& quad : m_Quads)
			{
				if (quad.UseTexture)
				{
					Renderer2D::DrawQuad(quad.Position, quad.Size, m_Texture2D, quad.TilingFactor, quad.TintColor);
				}
				else
				{
					Renderer2D::DrawQuad(quad.Position, quad.Size, quad.TintColor);
				}
			}

			for (auto& quad : m_RotatedQuads)
			{
				if (quad.UseTexture)
				{
					Renderer2D::DrawRotatedQuad(quad.Position, quad.Size, quad.Rotation, m_Texture2D, quad.TilingFactor, quad.TintColor);
				}
				else
				{
					Renderer2D::DrawRotatedQuad(quad.Position, quad.Size, quad.Rotation, quad.TintColor);
				}
			}

			Renderer2D::EndScene();
			m_Framebuffer->Unbind();
		}
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

		static bool	dockspaceOpen = true;
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







		ImGui::Begin("Library");
		ImGui::End();







		ImGui::Begin("Inspector");

		auto stats = Renderer2D::GetStatistics();

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

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Viewport");
		auto viewportPanelSize = ImGui::GetContentRegionAvail();

		if (m_ViewportSize != glm::vec2(viewportPanelSize.x, viewportPanelSize.y))
		{
			m_ViewportSize = { (uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y };
			m_Framebuffer->Resize(m_ViewportSize.x, m_ViewportSize.y);

			m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
		}

		auto textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2(0, 1), ImVec2(1, 0));

		ImGui::PopStyleVar();
		ImGui::End();






		ImGui::Begin("Game");
		ImGui::End();






		ImGui::Begin("Settings");
		ImGui::End();






		ImGui::Begin("Hierarchy");
		ImGui::End();





		ImGui::End();
	}
	void EditorLayer::OnEvent(Event& event)
	{
		m_CameraController.OnEvent(event);
	}
}