#include <MidnightEngine.h>

//#include "imgui/imgui.h"

class ExampleLayer : public MidnightEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (MidnightEngine::Input::IsKeyPressed(ME_KEY_TAB))
			ME_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		//ImGui::Begin("Test");
		//ImGui::Text("Hello World!");
		//ImGui::End();
	}

	void OnEvent(MidnightEngine::Event& event) override
	{
		if (event.GetEventType() == MidnightEngine::EventType::KeyPressed)
		{
			auto& e = (MidnightEngine::KeyPressedEvent&)event;
			if (e.GetKeyCode() == ME_KEY_TAB)
			{
				ME_TRACE("Tab key is pressed (event)!");
			}
			ME_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public MidnightEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

MidnightEngine::Application* MidnightEngine::CreateApplication()
{
	return new Sandbox();
}