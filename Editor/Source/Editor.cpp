#include <MidnightEngine.h>
#include <MidnightEngine/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace MidnightEngine
{
	class ChillEditor : public Application
	{
	public:
		ChillEditor()
			:Application("MidnightEngine")
		{
			PushLayer(new EditorLayer());
		}

		~ChillEditor() {}
	};

	Application* CreateApplication()
	{
		return new ChillEditor();
	}
}