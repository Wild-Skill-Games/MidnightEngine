#include <GaemEngien.h>

class Sandbox : public GaemEngien::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

GaemEngien::Application* GaemEngien::CreateApplication()
{
	return new Sandbox();
}