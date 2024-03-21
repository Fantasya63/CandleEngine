#pragma once
#include <Candle.h>

#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Sandbox2D : public Candle::Layer
{
public:
	Sandbox2D();

	void OnUpdate(Candle::Timestep ts) override;


	void OnEvent(Candle::Event& event) override
	{
		m_Camera2D.OnEvent(event);
	}


	virtual void OnImGuiRender() override;

private:
	//temp
	glm::vec3 m_Color = { 1.0f, 0.0f, 0.0f };

	Candle::ShaderLibrary m_ShaderLibrary;

	// -----------------------------------------
	//Candle::CameraController m_Camera = Candle::CameraController(glm::radians(50.0f), 1200.0f / 720.0f, 0.1f, 1000.0f, { 0.0f, 0.0f, 1.0f });
	Candle::Camera2DController m_Camera2D = Candle::Camera2DController((1200.0f / 720.0f));

	Candle::Ref<Candle::VertexBuffer> m_SquareVBO;
	Candle::Ref<Candle::IndexBuffer> m_SquareIBO;
	Candle::Ref<Candle::VertexArray> m_SquareVAO;
	Candle::Ref<Candle::Texture2D> m_SquareTexture;
};
