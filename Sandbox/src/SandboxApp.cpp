#include <TerribleEngine.h>

using namespace TerribleEngine;

class Sandbox : public Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Application* CreateApplication()
{
	return new Sandbox();
}