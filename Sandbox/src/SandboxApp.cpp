#include <Candle.h>


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

			in vec3 v_Color;
			in vec2 v_UV;

			void main()
			{
				outCol = texture(u_danboTex, v_UV);
			}

		)";

		m_Shader.reset(new Candle::Shader(vertexSrc, fragmentSrc));

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

			// Temp
			m_SquareTexture->Bind();
			Candle::Renderer::Submit(m_SquareVAO);

		}
		Candle::Renderer::EndScene();
	}

	void OnEvent(Candle::Event& event) override
	{
		
	}

private:
	//temp
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