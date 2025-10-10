#include "gepch.h"

#include "Buffer.h"
#include "Renderer.h"
#include "GameEngine/Log.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace GameEngine {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}