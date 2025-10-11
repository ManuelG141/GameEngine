#pragma once

#include "gepch.h"

namespace GameEngine {

	enum class ShaderDataType
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat3, Mat4,
		Bool,
	};

	uint32_t CalShaderTypeSize(const ShaderDataType& type);

	class Shader
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