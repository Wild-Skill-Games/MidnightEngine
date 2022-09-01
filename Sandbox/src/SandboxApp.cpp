#include <TerribleEngine.h>

class Sandbox : public TerribleEngine::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

TerribleEngine::Application* TerribleEngine::CreateApplication()
{
	return new Sandbox();
}