#pragma once


#include <glm/glm.hpp>

namespace Candle
{
	class Camera
	{
	public:
		Camera(float fov, float aspect, float zNear, float zFar, const glm::mat4& transform);
		
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
	};
}
