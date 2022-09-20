#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public MidnightEngine::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox() {}
};

MidnightEngine::Application* MidnightEngine::CreateApplication()
{
	return new Sandbox();
}