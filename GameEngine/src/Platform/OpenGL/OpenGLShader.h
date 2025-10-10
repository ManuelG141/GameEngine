#pragma once

#include "gepch.h"
#include "GameEngine/Renderer/Shader.h"

// TODO: ADD SHADER ABSTRACTION DEPENDING ON THE SELECTED RENDERERAPI

namespace GameEngine {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		uint32_t m_RendererID = 0;
	};
}