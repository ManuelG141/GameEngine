#include "gepch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace GameEngine {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		// ProjectionMatrix (left, right, bottom, top, near, far)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.f, 1.f)), m_ViewMatrix(1.f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		// the transform will only be rotated along the z axis
		glm::mat4 transform = glm::translate(glm::mat4(1.f), m_Position) *
			glm::rotate(glm::mat4(1.f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}