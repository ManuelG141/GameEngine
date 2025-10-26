#pragma once

#include "gepch.h"
#include "GameEngine/Core.h"
#include "RenderCommand.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Camera.h"

#include <glm/glm.hpp>

namespace GameEngine {

	class GE_API Renderer
	{
	public:
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::string& indexBufferkey, const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}