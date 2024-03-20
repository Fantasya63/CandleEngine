#include "cdpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include "Camera2D.h"

Candle::Camera2D::Camera2D(float left, float right, float bottom, float top)
	: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
{
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void Candle::Camera2D::SetProjection(float left, float right, float bottom, float top)
{
	m_ProjectionMatrix = glm::ortho(left, right, bottom, top);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void Candle::Camera2D::RecalculateViewMatrix()
{
	m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position);
	m_ViewMatrix = glm::rotate(m_ViewMatrix, glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	m_ViewMatrix = glm::inverse(m_ViewMatrix);
	
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}
