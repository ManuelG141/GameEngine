#pragma once

#include "gepch.h"
#include "GameEngine/Renderer/Shader.h"
#include <glad/glad.h>

namespace GameEngine {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const override;

		static GLenum ShaderType2GlType(const ShaderDataType& type);
	private:
		uint32_t m_RendererID = 0;
	};
}