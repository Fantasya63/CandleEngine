#include "cdpch.h"
#include "Buffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

#include "Renderer.h"

namespace Candle
{
	//TODO:: Change to avoid having to check every single frame?

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CD_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			return nullptr;
			
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		CD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}


	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{

		case RendererAPI::API::None:
			CD_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLIndexBuffer>(indices, count);
		}

		CD_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}