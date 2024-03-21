#include "Sandbox2D.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox 2D")
{

	Candle::BufferLayout layout = {
		{ Candle::ShaderDataType::Float3, "a_Position", false },
		{ Candle::ShaderDataType::Float3, "a_Color", false },
		{ Candle::ShaderDataType::Float2, "a_UV", false}
	};

	m_ShaderLibrary.Load("assets/shaders/TexturedShader.glsl");
	//m_Shader = Candle::Shader::Create("assets/shaders/TexturedShader.glsl");

	// ---------------------------------------------------------------------

	float squareVerts[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f
	};

	m_SquareVAO = Candle::VertexArray::Create();
	m_SquareVBO = Candle::VertexBuffer::Create(squareVerts, sizeof(squareVerts));
	m_SquareVBO->SetLayout(layout);

	m_SquareVAO->AddVertexBuffer(m_SquareVBO);
	m_SquareTexture = Candle::Texture2D::Create("assets/textures/2_Close_Up.png");

	uint32_t squareIndices[] = {
		0, 1, 2, 2, 1, 3
	};

	m_SquareIBO = Candle::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVAO->SetIndexBuffer(m_SquareIBO);
}

void Sandbox2D::OnUpdate(Candle::Timestep ts)
{
	Candle::RenderCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
	Candle::RenderCommand::Clear();

	m_Camera2D.Update(ts);

	auto shader = m_ShaderLibrary.Get("TexturedShader");
	Candle::Renderer2D::BeginScene(m_Camera2D);
	{
		shader->Bind();
		shader->SetFloat3("u_Color", m_Color);
		// Temp
		m_SquareTexture->Bind();
		Candle::Renderer2D::Submit(shader, m_SquareVAO);

	}
	Candle::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Test");
	ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));

	ImGui::End();
}