#include "cdpch.h"
#include "Renderer2D.h"

#include "Camera.h"

namespace Candle
{
	Scope<Renderer2D::SceneData> Renderer2D::s_SceneData = CreateScope<Renderer2D::SceneData>();


	void Renderer2D::Init()
	{
		RenderCommand::Init();
	}

	void Renderer2D::BeginScene(Camera2D& cam)
	{
		s_SceneData->ViewProjectionMatrix = cam.GetViewProjectionMatrix();
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::OnWindowResized(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer2D::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Model", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}