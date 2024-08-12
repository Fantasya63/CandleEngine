#pragma once
#include <Candle.h>
#include "Candle/Renderer/EditorCamera.h"

#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Candle {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();

		void OnUpdate(Timestep ts) override;


		void OnEvent(Event& event) override
		{
			m_EditorCamera.OnEvent(event);
		}


		virtual void OnImGuiRender() override;

	private:
		// Temp
		bool m_ViewportPanelResized = false;
		glm::vec2 m_LastViewportPanelSize = { 0.0f, 0.0f };

		// temp
		// glm::vec4 m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };

		// Camera2DController m_Camera2D = Camera2DController((1280.0f / 720.0f));
		EditorCamera m_EditorCamera;

		Ref<Texture2D> m_SquareTexture;
		float m_RotationSpeed = 1.0f;

		float m_Rotation = 0.0f;
		glm::vec2 m_TextureTiling = { 1.0f, 1.0f };

		
		bool m_ViewportFocused = false, m_ViewportHovered = false;
		

		Ref<Framebuffer> m_Framebuffer;
		Ref<Scene> m_ActiveScene;
	};

}