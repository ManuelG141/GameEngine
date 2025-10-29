#pragma once

#include "GameEngine/Core.h"
#include "RendererAPI.h"

namespace GameEngine {

	class RenderCommand
	{
	public:
		GE_API inline static void SetClearColor(const glm::vec4& color) // 0-1 Color Range
		{
			s_RendererAPI->SetClearColor(color);
		}

		GE_API inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		GE_API inline static void SetViewport(const glm::uvec4& viewport)
		{
			s_RendererAPI->SetViewport(viewport);
		}

		GE_API inline static void DrawIndexed(const std::string& key, const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(key, vertexArray);
		}

	private:
		static RendererAPI* s_RendererAPI;
	};

}