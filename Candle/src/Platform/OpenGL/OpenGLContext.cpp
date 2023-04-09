#include "cdpch.h"
#include "OpenGlContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Candle
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		CD_CORE_ASSERT(m_WindowHandle, "Window Handle is null!")
	}
	 
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CD_CORE_ASSERT(status, "Failed to initialize Glad.");

		CD_CORE_INFO("Initialized OpenGL Context");
		CD_CORE_INFO("  Vendor: {0}", (const char*) glGetString(GL_VENDOR));
		CD_CORE_INFO("  Renderer: {0}", (const char*) glGetString(GL_RENDERER));
		CD_CORE_INFO("  OpenGl version: {0}", (const char*) glGetString(GL_VERSION));

	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
