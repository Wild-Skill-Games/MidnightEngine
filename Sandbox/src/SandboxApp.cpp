#include <TerribleEngine.h>

class Sandbox : public Terrible::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Terrible::Application* Terrible::CreateApplication()
{
	return new Sandbox();
}