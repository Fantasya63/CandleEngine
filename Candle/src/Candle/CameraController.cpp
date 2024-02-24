#include "cdpch.h"
#include "CameraController.h"
#include "Candle/Input/Input.h"

void Candle::CameraController::Update(const Timestep& ts)
{
	if (Input::IsKeyPressed(CD_KEY_W))
	{
		// Move forward
	}
	else if (Input::IsKeyPressed(CD_KEY_S))
	{
		// Move Backward
	}

	if (Input::IsKeyPressed(CD_KEY_A))
	{
		// Move Left
	}
	else if (Input::IsKeyPressed(CD_KEY_D))
	{
		// Move Right
	}
}
