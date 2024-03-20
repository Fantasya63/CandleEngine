#include "cdpch.h"
#include "Camera2DController.h"
#include "Candle/Input/Input.h"
#include "Candle/Input/MouseButtons.h"


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>

Candle::Camera2DController::Camera2DController(float left, float right, float bottom, float top)
	: Camera2D(left, right, bottom, top)
{

}

void Candle::Camera2DController::Update(const Timestep& ts)
{
}

void Candle::Camera2DController::OnEvent(Candle::Event& event)
{
}

bool Candle::Camera2DController::OnWindowResized(WindowResizeEvent& e)
{
	return false;
}

bool Candle::Camera2DController::OnMouseScroll(MouseScrolledEvent& e)
{
	return false;
}
