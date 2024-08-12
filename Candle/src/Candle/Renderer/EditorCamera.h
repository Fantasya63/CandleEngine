#pragma once
#include "Candle/Events/Event.h"
#include "Candle/Events/ApplicationEvent.h"
#include "Candle/Events/MouseEvent.h"
#include "Candle/Scene/SceneCamera.h"
#include "Candle/Core/Timestep.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Candle
{
	class EditorCamera : public SceneCamera
	{
	public:
		EditorCamera();

		void OnUpdate(Timestep ts);
		void OnEvent(Event& event);

		glm::mat4 CalculateViewMatrix() const;

	private:
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_Speed = 3.5f;
		float m_MouseSensitivity = 5.0f;
		float m_Pitch = 0.0f;

		glm::vec3 m_Position{ 0.0f, 0.0f, 0.0f };
		glm::quat m_Rotation;
	};
}

