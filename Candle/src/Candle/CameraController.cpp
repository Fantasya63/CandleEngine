#include "cdpch.h"
#include "CameraController.h"
#include "Candle/Input/Input.h"
#include "Candle/Input/MouseButtons.h"


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>

Candle::CameraController::CameraController(float fov, float aspect, float zNear, float zFar, const glm::vec3& pos, glm::quat& rot)
	: Camera(fov, aspect, zNear, zFar, glm::translate(glm::mat4(1), pos))
{
	m_FOV = fov;
	m_Aspect = aspect;
	m_zNear = zNear;
	m_zFar = zFar;
	m_Position = pos;
	m_Rotation = rot;

	m_Forward = m_Rotation * glm::vec3(0.0f, 0.0f, -1.0f);
	Input::SetMouseMode(MouseMode::DISABLED);
}

static glm::vec2 lastMousePos;


void Candle::CameraController::Update(const Timestep& ts)
{
	if (!Input::IsMouseButtonPressed(CD_MOUSE_BUTTON_RIGHT)) {
		Input::SetMouseMode(MouseMode::NORMAL);
		lastMousePos = Input::GetMousePos();

		return;
	}
	Input::SetMouseMode(MouseMode::DISABLED);

	bool moved = false;
	glm::vec3 right = glm::cross(m_Forward, glm::vec3(0.0f, 1.0f, 0.0f));

	// Translate
	glm::vec3 direction = { 0.0f, 0.0f, 0.0f };

	// Forward Backward
	if (Input::IsKeyPressed(CD_KEY_W))
	{
		m_Position += m_Forward * m_Speed * ts.GetSeconds();
		moved = true;
	}
	else if (Input::IsKeyPressed(CD_KEY_S))
	{
		m_Position -= m_Forward * m_Speed * ts.GetSeconds();
		moved = true;
	}


	// Left and Right
	if (Input::IsKeyPressed(CD_KEY_A))
	{
		m_Position -= right * m_Speed * ts.GetSeconds();
		moved = true;
	}
	else if (Input::IsKeyPressed(CD_KEY_D))
	{
		m_Position += right * m_Speed * ts.GetSeconds();
		moved = true;
	}

	// Up and down
	if (Input::IsKeyPressed(CD_KEY_E)) {
		m_Position += glm::vec3(0.0f, 1.0f, 0.0f) * m_Speed * ts.GetSeconds();
		moved = true;
	}
	else if (Input::IsKeyPressed(CD_KEY_Q)) {
		m_Position -= glm::vec3(0.0f, 1.0f, 0.0f) * m_Speed * ts.GetSeconds();
		moved = true;
	}
	

	// Rotation
	glm::vec2 mousePos = Input::GetMousePos();
	glm::vec2 mouseDelta = mousePos - lastMousePos;
	lastMousePos = mousePos;

	if (mouseDelta.x != 0.0f || mouseDelta.y != 0.0f) {
		mouseDelta *= glm::vec2(-m_MouseSensitivity * ts.GetSeconds());	
		
		float targetPitch = m_Pitch + mouseDelta.y;

		if (targetPitch > 89.5f) {
			mouseDelta.y = 89.5f - m_Pitch;
			m_Pitch = 89.5f;
		}
		else if (targetPitch < -89.5f) {
			mouseDelta.y = -89.5f - m_Pitch;
			m_Pitch = -89.5f;
		}
		else {
			m_Pitch = targetPitch;
		}

		CD_CORE_TRACE("Pitch: {0}", m_Pitch);

		// Clamp Pitch
		
		glm::quat rot = glm::angleAxis(glm::radians(mouseDelta.y), right) * glm::angleAxis(glm::radians(mouseDelta.x), glm::vec3(0.0f, 1.0f, 0.0f));
		m_Forward = rot * m_Forward;
		moved = true;
	}

	if (moved) {
		RecalculateView();
		moved = false;
	}
}

void Candle::CameraController::RecalculateView()
{
	//m_Forward = m_Rotation * glm::vec3(0.0f, 0.0f, -1.0f);
	m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Forward, glm::vec3(0.0f, 1.0f, 0.0f));
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

}

void Candle::CameraController::OnEvent(Candle::Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowResizeEvent>(CD_BIND_EVENT_FN(CameraController::OnWindowResized));
	dispatcher.Dispatch<MouseScrolledEvent>(CD_BIND_EVENT_FN(CameraController::OnMouseScroll));
}

bool Candle::CameraController::OnWindowResized(WindowResizeEvent& e)
{
	uint32_t width, height;
	width = e.GetWidth();
	height = e.GetHeight();

	CD_CORE_TRACE((float)width / height);

	SetProjection(m_FOV, (float) width / height, m_zNear, m_zFar);

	return false;
}

bool Candle::CameraController::OnMouseScroll(MouseScrolledEvent& e)
{
	m_Speed += e.GetYOffset() * 0.1f;
	m_Speed = glm::clamp(m_Speed, 0.1f, 10.0f);
	return true;
}

