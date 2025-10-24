#pragma once

#include "gepch.h"
#include "GameEngine/Core.h"

namespace GameEngine {

	enum class GE_API ShaderDataType
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat3, Mat4,
		Bool,
	};

	uint32_t GE_API CalShaderTypeSize(const ShaderDataType& type);

	class GE_API Shader
	{
	public:
		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	private:
		uint32_t m_RendererID = 0;
	};
}