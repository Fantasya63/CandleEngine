#pragma once
#include "Candle/Renderer/Camera.h"
#include "Candle/Scene/SceneCamera.h"
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
	class CameraController : public SceneCamera
	{
	public:
		CameraController(const glm::vec3& pos, glm::quat& rot = glm::quatLookAt(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));

		void Update(const Timestep& ts);
		void OnEvent(Candle::Event& event);
		glm::mat4 CalculateViewMatrix()
		{
				return glm::lookAt(m_Position, m_Position + m_Forward, glm::vec3(0.0f, 1.0f, 0.0f));
		}

	private:
		const glm::vec3 GetRight() const { return m_Rotation * glm::vec3(1.0f, 0.0f, 0.0f); };

	private:
		bool OnWindowResized(WindowResizeEvent& e);
		bool OnMouseScroll(MouseScrolledEvent& e);
		void RecalculateView();

	public:
		float m_Speed = 3.5f;
		float m_MouseSensitivity = 5.0f;

	private:
		float m_FOV = 45.0f;
		float m_Aspect = 16.0f / 9.0f;
		float m_zNear, m_zFar;
		
		float m_Pitch = 0.0f;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Forward;
		glm::quat m_Rotation;
	};
}

