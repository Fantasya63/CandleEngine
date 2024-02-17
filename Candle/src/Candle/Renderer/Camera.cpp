#include "cdpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>


Candle::Camera::Camera(float fov, float aspect, float zNear, float zFar, const glm::mat4& transform)
{
	m_ProjectionMatrix = glm::perspective(fov, aspect, zNear, zFar);
	m_ViewMatrix = glm::inverse(transform);

	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}
