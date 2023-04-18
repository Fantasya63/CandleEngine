#include <Candle.h>


class ExampleLayer : public Candle::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		m_VertexArray.reset(Candle::VertexArray::Create());

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
		};

		m_VertexBuffer.reset(Candle::VertexBuffer::Create(vertices, sizeof(vertices)));



		Candle::BufferLayout layout = {
			{ Candle::ShaderDataType::Float3, "a_Position", false },
			{ Candle::ShaderDataType::Float3, "a_Color", false }

		};

		m_VertexBuffer->SetLayout(layout);


		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(Candle::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec4 a_Position;
			layout(location = 1) in vec3 a_Color;

			out vec3 v_Color;

			void main()
			{
				v_Color = a_Color;
				gl_Position = a_Position;
			}

		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 outCol;

			in vec3 v_Color;

			void main()
			{
				outCol = vec4(v_Color, 1.0);
			}

		)";

		m_Shader.reset(new Candle::Shader(vertexSrc, fragmentSrc));

		// ---------------------------------------------------------------------

		float squareVerts[] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
		};

		m_SquareVAO.reset(Candle::VertexArray::Create());
		m_SquareVBO.reset(Candle::VertexBuffer::Create(squareVerts, sizeof(squareVerts)));
		m_SquareVBO->SetLayout(layout);

		m_SquareVAO->AddVertexBuffer(m_SquareVBO);


		uint32_t squareIndices[] = {
			0, 1, 2, 2, 1, 3
		};

		m_SquareIBO.reset(Candle::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVAO->SetIndexBuffer(m_SquareIBO);
	}

	void OnUpdate() override
	{
		Candle::RenderCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		Candle::RenderCommand::Clear();

		Candle::Renderer::BeginScene();
		{
			m_Shader->Bind();
			Candle::Renderer::Submit(m_SquareVAO);

			//---------------------

			m_Shader->Bind();
			Candle::Renderer::Submit(m_VertexArray);

		}
		Candle::Renderer::EndScene();
	}

	void OnEvent(Candle::Event& event) override
	{
		
	}

private:
	//temp
	std::shared_ptr<Candle::Shader> m_Shader;
	std::shared_ptr<Candle::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Candle::IndexBuffer> m_IndexBuffer;
	std::shared_ptr<Candle::VertexArray> m_VertexArray;

	// -----------------------------------------

	std::shared_ptr<Candle::VertexBuffer> m_SquareVBO;
	std::shared_ptr<Candle::IndexBuffer> m_SquareIBO;
	std::shared_ptr<Candle::VertexArray> m_SquareVAO;
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