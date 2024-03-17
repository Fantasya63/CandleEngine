#include "cdpch.h"
#include "WindowsInput.h"

#include "Candle/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Candle
{
	Input* Input::s_Instance = new WindowsInput();

	bool Candle::WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	glm::vec2 WindowsInput::GetMousePosImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		return GetMousePosImpl().x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		return GetMousePosImpl().y;
	}
	void WindowsInput::SetMouseModeImpl(MouseMode mode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		

		switch (mode)
		{
		case Candle::MouseMode::NORMAL:
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			break;

		case Candle::MouseMode::HIDDEN:
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			break;
		case Candle::MouseMode::DISABLED:
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			break;
		default:
			CD_CORE_ASSERT(false, "Error. Unknown mouse mode.");
		}
		
	}
}
 