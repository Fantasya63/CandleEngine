#include "cdpch.h"
#include "PlatformWindows.h"
#include "GLFW/glfw3.h"

namespace Candle
{
	Platform* Platform::s_Instance = new PlatformWindows();

	float PlatformWindows::GetTimeImpl()
	{
		return glfwGetTime();
	}
}