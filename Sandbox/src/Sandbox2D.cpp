#include "Sandbox2D.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox 2D")
{
	m_SquareTexture = Candle::Texture2D::Create("Assets/textures/2_Close_Up.png");
}

void Sandbox2D::OnUpdate(Candle::Timestep ts)
{
	Candle::RenderCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
	Candle::RenderCommand::Clear();

	m_Camera2D.Update(ts);

	m_Rotation += glm::radians(m_RotationSpeed) * ts.GetSeconds();

	Candle::Renderer2D::BeginScene(m_Camera2D);
	{
		Candle::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_Color);
		Candle::Renderer2D::DrawQuad({ 0.0f, 1.0f }, { 1.0f, 1.0f }, m_SquareTexture, m_TextureTiling, m_Color);
		Candle::Renderer2D::DrawRotatedQuad({ 2.0f, 0.0f }, { 1.0f, 1.0f }, m_Rotation, m_Color);
		Candle::Renderer2D::DrawRotatedQuad({ 2.0f, 1.0f }, { 1.0f, 1.0f }, -m_Rotation, m_SquareTexture, m_TextureTiling, m_Color);
	}
	Candle::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Test");
	ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));
	ImGui::SliderFloat("Rotation Speed", &m_RotationSpeed, 0.0f, 360.0f);
	ImGui::InputFloat2("Tiling Input", glm::value_ptr(m_TextureTiling), "%.1f");
	ImGui::End();
}