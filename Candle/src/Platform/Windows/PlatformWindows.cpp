#include "cdpch.h"
#include "Candle/Core/Platform.h"

#include <GLFW/glfw3.h>

namespace Candle
{
	float Time::GetTime()
	{
		return (float)glfwGetTime();
	}
}