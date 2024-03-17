#include "cdpch.h"
#include "Candle/Core/Platform.h"

#include <GLFW/glfw3.h>

namespace Candle
{
	float Platform::GetTime()
	{
		return (float)glfwGetTime();
	}
}