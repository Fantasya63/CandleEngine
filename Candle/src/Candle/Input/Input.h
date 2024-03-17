#pragma once

#include "Candle/Input/KeyCodes.h"

#include <glm/glm.hpp>

namespace Candle
{
	enum class MouseMode {
		NORMAL = 0,
		HIDDEN,
		DISABLED
	};

	class Input
	{
	public:
		static bool IsKeyPressed(int keycode);
		
		static bool IsMouseButtonPressed(int button);
		static float GetMouseX();
		static float GetMouseY();
		static glm::vec2 GetMousePos();
		static void SetMouseMode(MouseMode mode);
	};
}