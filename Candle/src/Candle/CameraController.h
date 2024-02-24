#pragma once
#include "Candle/Renderer/Camera.h"
#include "Candle/Events/Event.h"
#include "Candle/Core/Timestep.h"

#include <glm/glm.hpp>

namespace Candle
{
	class CameraController : public Camera
	{
	public:

		void Update(const Timestep& ts);
		void OnEvent(Candle::Event& event);

	private:
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
	};
}

