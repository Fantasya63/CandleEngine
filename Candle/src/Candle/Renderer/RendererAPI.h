#pragma once
#include "glm/glm.hpp"

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
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() const = 0;

		//virtual void DrawIndexed(const std::shared_ptr<>) = 0;

		inline static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
}