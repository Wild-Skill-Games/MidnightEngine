#include <MidnightEngine.h>
#include <MidnightEngine/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class ChillEditor : public MidnightEngine::Application
{
public:
	ChillEditor()
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new EditorLayer());
	}

	~ChillEditor() {}
};

MidnightEngine::Application* MidnightEngine::CreateApplication()
{
	return new ChillEditor();
}