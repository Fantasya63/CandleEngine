#include <Candle.h>
#include "glm/glm.hpp"

#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"

class ExampleLayer : public Candle::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

		Candle::BufferLayout layout = {
			{ Candle::ShaderDataType::Float3, "a_Position", false },
			{ Candle::ShaderDataType::Float3, "a_Color", false },
			{ Candle::ShaderDataType::Float2, "a_UV", false}
		};

		m_Shader = Candle::Shader::Create("assets/shaders/TexturedShader.glsl");

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


	void OnUpdate(Candle::Timestep ts) override
	{
		Candle::RenderCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		Candle::RenderCommand::Clear();

		Candle::Renderer::BeginScene(m_Camera);
		{
			m_Shader->Bind();
			m_Shader->SetFloat3("u_Color", m_Color);
			// Temp
			m_SquareTexture->Bind();
			Candle::Renderer::Submit(m_Shader, m_SquareVAO);

		}
		Candle::Renderer::EndScene();
	}


	void OnEvent(Candle::Event& event) override
	{
		
	}


	virtual void OnImGuiRender()
	{
		ImGui::Begin("Test");
		ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
		ImGui::End();
	}

private:
	//temp
	glm::vec3 m_Color = { 1.0f, 0.0f, 0.0f };
	Candle::Ref<Candle::Shader> m_Shader;

	// -----------------------------------------
	Candle::Camera m_Camera = Candle::Camera(glm::radians(50.0f), 1200.0f / 720.0f, 0.1f, 1000.0f, glm::translate(glm::mat4(1.0), { 0.0f, 0.0f, 1.0f }));

	Candle::Ref<Candle::VertexBuffer> m_SquareVBO;
	Candle::Ref<Candle::IndexBuffer> m_SquareIBO;
	Candle::Ref<Candle::VertexArray> m_SquareVAO;
	Candle::Ref<Candle::Texture2D> m_SquareTexture;
};

class Sandbox : public Candle::Application
{
public:
	Sandbox()
	{
		ExampleLayer* layer = new ExampleLayer();
		PushLayer(layer);

	}
	~Sandbox()
	{

	}

private:
};

Candle::Application* Candle::CreateApplication()
{
	return new Sandbox();
}