#include "gepch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace GameEngine {

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::SetViewport(const glm::uvec4& viewport)
	{
		glViewport(viewport.x, viewport.y, viewport.z, viewport.w);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::string& key, const std::shared_ptr<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer(key)->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}