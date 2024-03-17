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

		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
		inline static glm::vec2 GetMousePos() { return s_Instance->GetMousePosImpl(); }

		inline static void SetMouseMode(MouseMode mode) { s_Instance->SetMouseModeImpl(mode); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;

		virtual glm::vec2 GetMousePosImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual void SetMouseModeImpl(MouseMode mode) = 0;


	private:
		static Input* s_Instance;
	};
}