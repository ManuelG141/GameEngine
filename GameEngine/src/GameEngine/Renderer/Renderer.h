#pragma once

#include "gepch.h"
#include "GameEngine/Core.h"
#include "RenderCommand.h"

namespace GameEngine {

	class GE_API Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::string& key, const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}