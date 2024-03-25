#pragma once
#include "RenderCommand.h"
#include "Candle/Renderer/Camera.h"
#include "Candle/Renderer/Shader.h"

namespace Candle
{ 
	class Renderer 
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(Camera& cam); //TODO, Take in cam, environment, lights, etc
		static void EndScene();
		static void OnWindowResized(uint32_t width, uint32_t height);
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> s_SceneData;
	};
}