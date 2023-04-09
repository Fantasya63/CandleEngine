#pragma once

#include "Candle/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Candle
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}

