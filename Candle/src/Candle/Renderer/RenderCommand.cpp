#include "cdpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Candle
{
	// TODO: Make Render API Agnostic
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI; //No need to worry about memory leak as this needs to be cleared at the end of the app anyway
}