#include "cdpch.h"
#include "Shader.h"
#include "Candle/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Candle
{
	Ref<Shader> Candle::Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CD_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
		}

		CD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}