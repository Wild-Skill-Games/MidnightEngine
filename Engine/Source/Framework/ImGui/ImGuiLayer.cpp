#include "mepch.h"
#include "ImGuiLayer.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "MidnightEngine/Core/Application.h"

// TEMPORARY
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace MidnightEngine
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")

	{
	}
	ImGuiLayer::~ImGuiLayer() {}

	void ImGuiLayer::OnAttach()
	{
		ME_PROFILE_FUNCTION();

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		(void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
		// io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; //Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;	// Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
		// io.ConfigFlags |= ImGuiViewportFlags_NoTaskBarIcon;
		// io.ConfigFlags |= ImGuiViewportFlags_NoAutoMerge;

		auto mediumFont = io.Fonts->AddFontFromFileTTF("assets/fonts/Inter/Inter-Medium.ttf", 16.0f);
		auto boldFont = io.Fonts->AddFontFromFileTTF("assets/fonts/Inter/Inter-Bold.ttf", 16.0f);

		io.FontDefault = mediumFont;

		// Setup Dear ImGui style
		//ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to other platforms
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0;
			style.Colors[ImGuiCol_WindowBg].w = 1;
		}

		SetDarkThemeColors();

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}
	void ImGuiLayer::OnDetach()
	{
		ME_PROFILE_FUNCTION();

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		ME_PROFILE_FUNCTION();

		if (m_BlockEvents)
		{
			ImGuiIO& io = ImGui::GetIO();
			event.Handled |= event.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
			event.Handled |= event.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
		}
	}

	void ImGuiLayer::Begin()
	{
		ME_PROFILE_FUNCTION();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	void ImGuiLayer::End()
	{
		ME_PROFILE_FUNCTION();

		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			auto* backup_current_context = glfwGetCurrentContext();

			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::SetDarkThemeColors()
	{
		ImGui::StyleColorsDark();

		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);

		colors[ImGuiCol_Header] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);

		colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);

		colors[ImGuiCol_FrameBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.0f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);

		colors[ImGuiCol_Tab] = ImVec4(0.07f, 0.07f, 0.07f, 1.0f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
		colors[ImGuiCol_TabActive] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.07f, 0.07f, 1.0f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);

		colors[ImGuiCol_TitleBg] = ImVec4(0.07f, 0.07f, 0.07f, 1.0f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);

		colors[ImGuiCol_Separator] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
}