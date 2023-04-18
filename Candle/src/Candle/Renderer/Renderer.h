#pragma once
#include "RenderCommand.h"

namespace Candle
{ 

	class Renderer 
	{
	public:
		static void BeginScene(); //TODO, Take in cam, environment, lights, etc
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}