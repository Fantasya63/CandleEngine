#pragma once
#include "Candle/Renderer/RendererAPI.h"
#include "Candle/Renderer/RendererAPI.h"

namespace Candle{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) const override;
		virtual void Clear() const override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
		virtual void SetViewport(uint32_t minX, uint32_t minY, uint32_t maxX, uint32_t maxY) override;

	};
}

