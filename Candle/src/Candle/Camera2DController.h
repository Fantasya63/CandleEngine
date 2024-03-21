#pragma once
#include "Candle/Renderer/Camera2D.h"
#include "Candle/Events/Event.h"
#include "Candle/Events/ApplicationEvent.h"
#include "Candle/Events/MouseEvent.h"
#include "Candle/Core/Timestep.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

// TODO: Change to composition instead of inheritance?

namespace Candle
{
	class Camera2DController : public Camera2D
	{
	public:
		Camera2DController(float aspect, const glm::vec3& pos = glm::vec3(0.0f, 0.0f, 0.0f), float zoom = 1.0f);
		void Update(const Timestep& ts);
		void OnEvent(Candle::Event& event);

	private:
		bool OnWindowResized(WindowResizeEvent& e);
		bool OnMouseScroll(MouseScrolledEvent& e);
		
	public:
		float m_Speed = 3.5f;
		float m_RotationSpeed = 5.0f;
		float m_Zoom;

	private:
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_Aspect;
	};
}

