#pragma once
#include "glm/glm.hpp"
#include "VertexArray.h"
#include <memory>


namespace Candle
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};

	public:
		virtual void SetClearColor(const glm::vec4& color) const = 0;
		virtual void Clear() const = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
}