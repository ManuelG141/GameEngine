#pragma once

#include "gepch.h"
#include "VertexArray.h"
#include <glm/glm.hpp>

namespace GameEngine {

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};
	public:
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void SetViewport(const glm::uvec4& viewport) = 0;

		virtual void DrawIndexed(const std::string& key, const std::shared_ptr<VertexArray>& vertexArray) = 0;
	
		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};

}