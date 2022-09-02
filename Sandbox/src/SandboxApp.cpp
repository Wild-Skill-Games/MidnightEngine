#include <MidnightEngine.h>

class ExampleLayer : public MidnightEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate()
	{
		ME_INFO("ExampleLayer::Update");
	}

	void OnEvent(MidnightEngine::Event& event) override
	{
		ME_TRACE("{0}", event);
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