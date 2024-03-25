#pragma once
#include "RenderCommand.h"

#include "Candle/Renderer/Camera2D.h"
#include "Candle/Renderer/Texture.h"

namespace Candle
{ 
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(Camera2D& cam); //TODO, Take in cam, environment, lights, etc
		static void EndScene();
		static void OnWindowResized(uint32_t width, uint32_t height);
		//static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		static void DrawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color);
		
		static void DrawQuad(const glm::vec2& position, const glm::vec2& scale, 
			const Ref<Texture2D>& texture, const glm::vec2& tiling, const glm::vec4& tintColor);
		
		static void DrawQuad(const glm::vec3& position, const glm::vec2& scale,
			const Ref<Texture2D>& texture, const glm::vec2& tiling, const glm::vec4& tintColor);
	

		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& scale, float rotation, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& scale, float rotation, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& scale, float rotation, const Ref<Texture2D>& texture, const glm::vec2& tiling, const glm::vec4& tintColor);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& scale, float rotation, const Ref<Texture2D>& texture, const glm::vec2& tiling, const glm::vec4& tintColor);

		
		static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, const glm::vec2& tiling, const glm::vec4& tintColor);


		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}