#include "gepch.h"

#include "Shader.h"
#include "Renderer.h"
#include "GameEngine/Log.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace GameEngine {
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}