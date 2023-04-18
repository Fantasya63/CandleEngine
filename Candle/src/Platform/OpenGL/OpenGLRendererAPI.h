#pragma once
#include "Candle/Renderer/RendererAPI.h"
#include "Candle/Renderer/RendererAPI.h"

namespace Candle{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) const override;
		virtual void Clear() const override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

	};
}

