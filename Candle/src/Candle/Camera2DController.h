#pragma once
#include "Candle/Renderer/Camera2D.h"
#include "Candle/Events/Event.h"
#include "Candle/Events/ApplicationEvent.h"
#include "Candle/Events/MouseEvent.h"
#include "Candle/Core/Timestep.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Candle
{
	class Camera2DController : public Camera2D
	{
	public:
		Camera2DController(float left, float right, float bottom, float top);
		void Update(const Timestep& ts);
		void OnEvent(Candle::Event& event);

	private:
		bool OnWindowResized(WindowResizeEvent& e);
		bool OnMouseScroll(MouseScrolledEvent& e);
		
	public:
		float m_Speed = 3.5f;
		float m_RotationSpeed = 5.0f;
	};
}

