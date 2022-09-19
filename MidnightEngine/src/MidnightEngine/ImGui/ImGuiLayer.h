#pragma once

#include "MidnightEngine/Core/Layer.h"

#include "MidnightEngine/Events/KeyEvent.h"
#include "MidnightEngine/Events/MouseEvent.h"
#include "MidnightEngine/Events/ApplicationEvent.h"


namespace MidnightEngine
{
	class MIDNIGHT_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}