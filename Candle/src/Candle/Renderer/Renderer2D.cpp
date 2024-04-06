#include "cdpch.h"
#include "Renderer2D.h"

#include "Candle/Core/Platform.h"

#include "Candle/Renderer/Camera.h"
#include "Candle/Renderer/Shader.h"
#include "Candle/Renderer/Texture.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Candle
{
	struct RendererData
	{
		Candle::Ref<Candle::VertexArray> QuadVAO;
		Candle::Ref<Candle::Shader> SimpleShader2D;
		Candle::Ref<Candle::Texture2D> WhiteTexture;
	};

	static RendererData* s_Renderer2DData;


	void Renderer2D::Init()
	{
		CD_PROFILE_FUNCTION();

		s_Renderer2DData = new RendererData();
		s_Renderer2DData->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Renderer2DData->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		Candle::BufferLayout layout = {
			{ Candle::ShaderDataType::Float3, "a_Position", false },
			{ Candle::ShaderDataType::Float2, "a_UV", false}
		};

		s_Renderer2DData->SimpleShader2D = Shader::Create("assets/shaders/SimpleShader2D.glsl");
		
		float squareVerts[] = {
			// Position			// UV
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f
		};

		s_Renderer2DData->QuadVAO = Candle::VertexArray::Create();

		Ref<VertexBuffer> squareVBO;
		squareVBO = Candle::VertexBuffer::Create(squareVerts, sizeof(squareVerts));
		squareVBO->SetLayout(layout);

		s_Renderer2DData->QuadVAO->AddVertexBuffer(squareVBO);
		//m_SquareTexture = Candle::Texture2D::Create("assets/textures/2_Close_Up.png");

		uint32_t squareIndices[] = {
			0, 1, 2, 2, 1, 3
		};

		Ref<IndexBuffer> squareIBO;
		squareIBO = Candle::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		s_Renderer2DData->QuadVAO->SetIndexBuffer(squareIBO);
	}


	void Renderer2D::Shutdown()
	{
		CD_PROFILE_FUNCTION();
		delete s_Renderer2DData;
	}


	void Renderer2D::BeginScene(Camera2D& cam)
	{
		s_Renderer2DData->SimpleShader2D->Bind();
		s_Renderer2DData->SimpleShader2D->SetMat4("u_ViewProjection", cam.GetViewProjectionMatrix());
	}


	void Renderer2D::EndScene()
	{
	}


	void Renderer2D::OnWindowResized(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}


	void Renderer2D::DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, const glm::vec2& tiling, const glm::vec4& tintColor)
	{
		s_Renderer2DData->SimpleShader2D->SetMat4("u_Model", transform);
		texture->Bind(0);

		s_Renderer2DData->SimpleShader2D->SetFloat2("u_TilingFactor", tiling);
		s_Renderer2DData->SimpleShader2D->SetFloat4("u_TintColor", tintColor);
		s_Renderer2DData->SimpleShader2D->SetFloat("u_Time", Time::GetTime());

		s_Renderer2DData->QuadVAO->Bind();
		RenderCommand::DrawIndexed(s_Renderer2DData->QuadVAO);
	}


	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(position.x, position.y, 0.0f), scale, color);
	}
	

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& scale,
		const Ref<Texture2D>& texture, const glm::vec2& tiling, const glm::vec4& tintColor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, scale, texture, tiling, tintColor);
	}


	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color)
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
		model = glm::scale(model, glm::vec3(scale.x, scale.y, 1.0));

		DrawQuad(model, s_Renderer2DData->WhiteTexture, glm::vec2(1.0f, 1.0f), color);
	}


	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& scale,
		const Ref<Texture2D>& texture, const glm::vec2& tiling, const glm::vec4& tintColor)
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
		model = glm::scale(model, glm::vec3(scale.x, scale.y, 1.0));

		DrawQuad(model, texture, tiling, tintColor);
	}


	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& scale, float rotation, const glm::vec4& color)
	{
		DrawRotatedQuad(glm::vec3(position.x, position.y, 0.0f), scale, rotation, color);
	}


	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& scale, float rotation,
		const Ref<Texture2D>& texture, const glm::vec2& tiling, const glm::vec4& tintColor)
	{
		DrawRotatedQuad(glm::vec3(position.x, position.y, 0.0f), scale, rotation, texture, tiling, tintColor);
	}


	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& scale, float rotation, const glm::vec4& color)
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
		model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(scale.x, scale.y, 1.0));
		
		DrawQuad(model, s_Renderer2DData->WhiteTexture, glm::vec2(1.0f, 1.0f), color);
	}


	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& scale, float rotation,
		const Ref<Texture2D>& texture, const glm::vec2& tiling, const glm::vec4& tintColor)
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
		model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(scale.x, scale.y, 1.0));

		DrawQuad(model, texture, tiling, tintColor);
	}
}