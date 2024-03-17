#pragma once

#include "Candle/Input/Input.h"

namespace Candle{

	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual glm::vec2 GetMousePosImpl() override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual void SetMouseModeImpl(MouseMode mode) override;
	};
}

