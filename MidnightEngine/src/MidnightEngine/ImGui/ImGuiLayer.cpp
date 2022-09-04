#include "mepch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include <GLFW/glfw3.h>

#include "MidnightEngine/Application.h"

namespace MidnightEngine
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")

	{

	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// TODO : Make it Midnight Keycodes

		// Directional Keys
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;

		// Special Keys Left Side
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_CapsLock] = GLFW_KEY_CAPS_LOCK;
		io.KeyMap[ImGuiKey_LeftShift] = GLFW_KEY_LEFT_SHIFT;
		io.KeyMap[ImGuiKey_LeftCtrl] = GLFW_KEY_LEFT_CONTROL;
		io.KeyMap[ImGuiKey_LeftAlt] = GLFW_KEY_LEFT_ALT;

		// Special Keys Right Side
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_RightShift] = GLFW_KEY_RIGHT_SHIFT;
		io.KeyMap[ImGuiKey_RightCtrl] = GLFW_KEY_RIGHT_CONTROL;
		io.KeyMap[ImGuiKey_RightAlt] = GLFW_KEY_RIGHT_ALT;

		// Utility Keys
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;

		// Digits
		io.KeyMap[ImGuiKey_0] = GLFW_KEY_0;
		io.KeyMap[ImGuiKey_1] = GLFW_KEY_1;
		io.KeyMap[ImGuiKey_2] = GLFW_KEY_2;
		io.KeyMap[ImGuiKey_3] = GLFW_KEY_3;
		io.KeyMap[ImGuiKey_4] = GLFW_KEY_4;
		io.KeyMap[ImGuiKey_5] = GLFW_KEY_5;
		io.KeyMap[ImGuiKey_6] = GLFW_KEY_6;
		io.KeyMap[ImGuiKey_7] = GLFW_KEY_7;
		io.KeyMap[ImGuiKey_8] = GLFW_KEY_8;
		io.KeyMap[ImGuiKey_9] = GLFW_KEY_9;

		// Letters
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_B] = GLFW_KEY_B;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_D] = GLFW_KEY_D;
		io.KeyMap[ImGuiKey_E] = GLFW_KEY_E;
		io.KeyMap[ImGuiKey_F] = GLFW_KEY_F;
		io.KeyMap[ImGuiKey_G] = GLFW_KEY_G;
		io.KeyMap[ImGuiKey_H] = GLFW_KEY_H;
		io.KeyMap[ImGuiKey_I] = GLFW_KEY_I;
		io.KeyMap[ImGuiKey_J] = GLFW_KEY_J;
		io.KeyMap[ImGuiKey_K] = GLFW_KEY_K;
		io.KeyMap[ImGuiKey_L] = GLFW_KEY_L;
		io.KeyMap[ImGuiKey_M] = GLFW_KEY_M;
		io.KeyMap[ImGuiKey_N] = GLFW_KEY_N;
		io.KeyMap[ImGuiKey_O] = GLFW_KEY_O;
		io.KeyMap[ImGuiKey_P] = GLFW_KEY_P;
		io.KeyMap[ImGuiKey_Q] = GLFW_KEY_Q;
		io.KeyMap[ImGuiKey_R] = GLFW_KEY_R;
		io.KeyMap[ImGuiKey_S] = GLFW_KEY_S;
		io.KeyMap[ImGuiKey_T] = GLFW_KEY_T;
		io.KeyMap[ImGuiKey_U] = GLFW_KEY_U;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_W] = GLFW_KEY_W;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event)
	{

	}
}