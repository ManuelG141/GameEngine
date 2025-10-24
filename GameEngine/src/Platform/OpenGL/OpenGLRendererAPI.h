#pragma once

#include "GameEngine/Renderer/RendererAPI.h"

namespace GameEngine {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void SetViewport(const glm::uvec4& viewport) override;

		virtual void DrawIndexed(const std::string& key, const std::shared_ptr<VertexArray>& vertexArray) override;

	};

}