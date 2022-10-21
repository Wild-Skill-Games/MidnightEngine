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
		virtual void OnEvent(Event& event) override;

		void Begin();
		void End();

		inline void BlockEvents(bool block) { m_BlockEvents = block; }

		static void SetDarkThemeColors();

	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}