#include "mepch.h"
#include "Layer.h"

namespace MidnightEngine
{
	Layer::Layer(const std::string& debugName)
		:m_DebugName(debugName)
	{
	}

	Layer::~Layer() {}
}