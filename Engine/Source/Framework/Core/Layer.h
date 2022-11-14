#pragma once

#include "MidnightEngine/Core/Core.h"
#include "MidnightEngine/Core/Timestep.h"

#include "MidnightEngine/Events/Event.h"

namespace MidnightEngine
{
	class MIDNIGHT_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}