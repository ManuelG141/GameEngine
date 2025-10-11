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

	uint32_t CalShaderTypeSize(const ShaderDataType& type)
	{
		switch (type)
		{
			case ShaderDataType::None:		return 0;
			case ShaderDataType::Float:		return 4;
			case ShaderDataType::Float2:	return 4 * 2;
			case ShaderDataType::Float3:	return 4 * 3;
			case ShaderDataType::Float4:	return 4 * 4;
			case ShaderDataType::Int:		return 4;
			case ShaderDataType::Int2:		return 4 * 2;
			case ShaderDataType::Int3:		return 4 * 3;
			case ShaderDataType::Int4:		return 4 * 4;
			case ShaderDataType::Mat3:		return 4 * 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4 * 4;
			case ShaderDataType::Bool:		return 1;
		}

		GE_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
}