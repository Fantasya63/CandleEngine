#include "cdpch.h"
#include "EditorCamera.h"

#include "Candle/Events/ApplicationEvent.h"
#include "Candle/Input/Input.h"
#include "Candle/Input/MouseButtons.h"

#include <glm/gtx/quaternion.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


namespace Candle {

	static glm::vec2 lastMousePos;

	EditorCamera::EditorCamera()
		: SceneCamera()
	{
	}

	void EditorCamera::OnUpdate(Timestep ts)
	{
		if (!Input::IsMouseButtonPressed(CD_MOUSE_BUTTON_RIGHT)) {
			Input::SetMouseMode(MouseMode::NORMAL);
			lastMousePos = Input::GetMousePos();

			return;
		}
		Input::SetMouseMode(MouseMode::DISABLED);

		bool moved = false;
		glm::vec3 forward = m_Rotation * glm::vec3(0.0f, 0.0f, -1.0f);


		if (Input::IsKeyPressed(Keycode::W))
		{
			m_Position += forward * m_Speed * ts.GetSeconds();
		}
		else if (Input::IsKeyPressed(Keycode::S))
		{
			m_Position -= forward * m_Speed * ts.GetSeconds();
		}

		//CD_CORE_INFO("Position: {0}, {1}, {2}", m_Position.x, m_Position.y, m_Position.z);
	
		// Rotation
		glm::vec2 mousePos = Input::GetMousePos();
		glm::vec2 mouseDelta = mousePos - lastMousePos;
		lastMousePos = mousePos;

		if (mouseDelta.x != 0.0f || mouseDelta.y != 0.0f) {
			mouseDelta *= glm::vec2(-m_MouseSensitivity * ts.GetSeconds());

			float targetPitch = m_Pitch + mouseDelta.y;

			// Clamp Pitch
			if (targetPitch > 89.5f) {
				mouseDelta.y = 89.5f - m_Pitch;
				m_Pitch = 89.5f;
			}
			else if (targetPitch < -90.0f) {
				mouseDelta.y = -90.0f - m_Pitch;
				m_Pitch = -90.0f;
			}
			else {
				m_Pitch = targetPitch;
			}
			glm::vec3 right = glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f));
			glm::quat pitch = glm::angleAxis(glm::radians(mouseDelta.y), right);
			glm::quat yaw = glm::angleAxis(glm::radians(mouseDelta.x), glm::vec3(0.0f, 1.0f, 0.0f));
			m_Rotation = yaw * pitch * m_Rotation;
		}
	}

	void EditorCamera::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowResizeEvent>(CD_BIND_EVENT_FN(OnWindowResized));
	}

	glm::mat4 EditorCamera::CalculateViewMatrix() const
	{
		return glm::translate(glm::mat4(1.0f), -m_Position) * glm::mat4(glm::inverse(m_Rotation));
	}

	bool EditorCamera::OnWindowResized(WindowResizeEvent& e)
	{
		SetViewportSize(e.GetWidth(), e.GetHeight());

		return false;
	}

}
