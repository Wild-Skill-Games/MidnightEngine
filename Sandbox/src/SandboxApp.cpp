#include <MidnightEngine.h>

class Sandbox : public MidnightEngine::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

MidnightEngine::Application* MidnightEngine::CreateApplication()
{
	return new Sandbox();
}