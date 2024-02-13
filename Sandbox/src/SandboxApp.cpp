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

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec4 a_Position;
			layout(location = 1) in vec3 a_Color;
			layout(location = 2) in vec2 a_UV;

			out vec3 v_Color;
			out vec2 v_UV;

			void main()
			{
				v_UV = a_UV;
				v_Color = a_Color;
				gl_Position = a_Position;
			}

		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 outCol;

			uniform sampler2D u_danboTex;
			uniform vec3 u_Color;

			in vec3 v_Color;
			in vec2 v_UV;

			void main()
			{
				vec3 temp = texture(u_danboTex, v_UV).rgb;
				temp = temp * u_Color;				

				outCol = vec4(temp, 1.0);
			}

		)";

		m_Shader = Candle::Shader::Create(vertexSrc, fragmentSrc);

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

		Candle::Renderer::BeginScene();
		{
			m_Shader->Bind();
			m_Shader->SetFloat3("u_Color", m_Color);
			// Temp
			m_SquareTexture->Bind();
			Candle::Renderer::Submit(m_SquareVAO);

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
	glm::vec3 m_Color;
	Candle::Ref<Candle::Shader> m_Shader;

	// -----------------------------------------

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