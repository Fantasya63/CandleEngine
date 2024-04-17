#include "cdpch.h"
#include "Camera2DController.h"
#include "Candle/Input/Input.h"
#include "Candle/Input/MouseButtons.h"


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>


Candle::Camera2DController::Camera2DController(float aspect, const glm::vec3& pos, float zoom)
	: m_Zoom(zoom), Camera2D(-aspect, aspect, -zoom, zoom), m_Aspect(aspect)
{
	m_CameraPosition = pos;
	SetPosition(pos);
}

void Candle::Camera2DController::Update(const Timestep& ts)
{
	if (Input::IsKeyPressed(Keycode::A))
		m_CameraPosition -= glm::vec3(1.0f, 0.0f, 0.0f) * ts.GetSeconds();
	else if (Input::IsKeyPressed(Keycode::D)) 
		m_CameraPosition += glm::vec3(1.0f, 0.0f, 0.0f) * ts.GetSeconds();
	
	if (Input::IsKeyPressed(Keycode::W))
		m_CameraPosition += glm::vec3(0.0f, 1.0f, 0.0f) * ts.GetSeconds();
	else if (Input::IsKeyPressed(Keycode::S))
		m_CameraPosition -= glm::vec3(0.0f, 1.0f, 0.0f) * ts.GetSeconds();
	
	SetPosition(m_CameraPosition);
	//CD_CORE_TRACE("Position: {0}, {1}, {2}", m_CameraPosition.x, m_CameraPosition.y, m_CameraPosition.z);
}

void Candle::Camera2DController::OnEvent(Candle::Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowResizeEvent>(CD_BIND_EVENT_FN(OnWindowResized));
	dispatcher.Dispatch<MouseScrolledEvent>(CD_BIND_EVENT_FN(OnMouseScroll));
}

void Candle::Camera2DController::ResizeBounds(float width, float height)
{
	m_Aspect = width / height;
	SetProjection(-m_Aspect * m_Zoom, m_Aspect * m_Zoom, -m_Zoom, m_Zoom);
}


bool Candle::Camera2DController::OnWindowResized(WindowResizeEvent& e)
{
	ResizeBounds(e.GetWidth(), e.GetHeight());

	return false;
}

bool Candle::Camera2DController::OnMouseScroll(MouseScrolledEvent& e)
{
	m_Zoom -= e.GetYOffset() * 0.1f;
	SetProjection(-m_Aspect * m_Zoom, m_Aspect * m_Zoom, -m_Zoom, m_Zoom);
	return false;
}
