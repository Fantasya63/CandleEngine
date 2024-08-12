#include "cdpch.h"
#include "Renderer.h"
#include "Renderer2D.h"

#include "Camera.h"

namespace Candle
{
	// Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();
	struct RendererData
	{
		glm::mat4 ViewProjectionMatrix;

		Ref<VertexArray> QuadVAO;
		Ref<Shader> QuadShader;
	};

	static RendererData* s_RendererData;


	void Renderer::Init()
	{
		CD_PROFILE_FUNCTION();

		RenderCommand::Init();

		s_RendererData = new RendererData();

		//s_RendererData->QuadShader = Shader::Create("assets/shaders/SimpleShader.glsl");
		s_RendererData->QuadShader = Shader::Create("assets/shaders/SimpleShader.glsl");


		Candle::BufferLayout layout = {
			{ Candle::ShaderDataType::Float3, "a_Position", false },
			{ Candle::ShaderDataType::Float2, "a_UV", false}
		};

		float squareVerts[] = {
			// Position			// UV
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f
		};

		s_RendererData->QuadVAO = Candle::VertexArray::Create();

		Ref<VertexBuffer> squareVBO;
		squareVBO = Candle::VertexBuffer::Create(squareVerts, sizeof(squareVerts));
		squareVBO->SetLayout(layout);

		s_RendererData->QuadVAO->AddVertexBuffer(squareVBO);
		//m_SquareTexture = Candle::Texture2D::Create("assets/textures/2_Close_Up.png");

		uint32_t squareIndices[] = {
			0, 1, 2, 2, 1, 3
		};

		Ref<IndexBuffer> squareIBO;
		squareIBO = Candle::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		s_RendererData->QuadVAO->SetIndexBuffer(squareIBO);


		Renderer2D::Init();
	}

	void Renderer::Shutdown()
	{
		CD_PROFILE_FUNCTION();
		
		Renderer2D::Shutdown();

		delete s_RendererData;
	}

	void Renderer::BeginScene(Camera& cam, const glm::mat4& view)
	{
		s_RendererData->ViewProjectionMatrix = cam.GetProjectionMatrix() * view;
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::OnWindowResized(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_RendererData->ViewProjectionMatrix);
		shader->SetMat4("u_Model", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::RenderQuad(const Ref<Shader>& shader, const glm::mat4& transform)
	{
		Renderer::Submit(shader, s_RendererData->QuadVAO, transform);
	}
	void Renderer::RenderQuad(const glm::mat4& transform)
	{
		Renderer::Submit(s_RendererData->QuadShader, s_RendererData->QuadVAO, transform);
	}
}