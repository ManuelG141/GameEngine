#pragma once

#include "GameEngine/Core.h"
#include <glm/glm.hpp>

namespace GameEngine {

	class OrthographicCamera // For 2D rendering at the moment
	{
	public:
		GE_API OrthographicCamera(float left, float right, float bottom, float top);

		GE_API void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
		GE_API inline const glm::vec3& GetPosition() const { return m_Position; }

		GE_API void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
		GE_API inline const float& GetRotation() const { return m_Rotation; }

		GE_API inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		GE_API inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		GE_API inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.f, 0.f, 0.f };
		float m_Rotation = 0.f; // Only possible to rotate around x axis right now
	};
}