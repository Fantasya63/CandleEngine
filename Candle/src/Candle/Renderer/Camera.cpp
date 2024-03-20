#include "cdpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include "Camera2D.h"


Candle::Camera::Camera(float fov, float aspect, float zNear, float zFar, const glm::mat4& transform)
{
	SetProjection(fov, aspect, zNear, zFar);
	m_ViewMatrix = glm::inverse(transform);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void Candle::Camera::SetProjection(float fov, float aspect, float zNear, float zFar)
{
	m_ProjectionMatrix = glm::perspective(fov, aspect, zNear, zFar);
}
