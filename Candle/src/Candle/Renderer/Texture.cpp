#include "cdpch.h"
#include "Texture.h"
#include "Renderer.h"

#include "Platform/OpenGl/OpenGlTexture.h"

namespace Candle
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CD_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		}

		CD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
