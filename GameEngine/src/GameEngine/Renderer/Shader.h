#pragma once

#include "gepch.h"

namespace GameEngine {
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& framentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;
	private:
		uint32_t m_RendererID;
	};
}