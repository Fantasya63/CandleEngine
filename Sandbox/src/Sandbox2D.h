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
	glm::vec4 m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };
	
	Candle::Camera2DController m_Camera2D = Candle::Camera2DController((1200.0f / 720.0f));

	Candle::Ref<Candle::Texture2D> m_SquareTexture;
	float m_RotationSpeed = 1.0f;

	float m_Rotation = 0.0f;
	glm::vec2 m_TextureTiling = { 1.0f, 1.0f };
};
