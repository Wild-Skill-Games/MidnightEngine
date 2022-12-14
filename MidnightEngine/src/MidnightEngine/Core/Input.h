#pragma once

#include "MidnightEngine/Core/Core.h"

namespace MidnightEngine
{
	class MIDNIGHT_API Input
	{
	public:
		static bool IsKeyPressed(int keycode);

		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}