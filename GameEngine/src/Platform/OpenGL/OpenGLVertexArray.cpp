#include "gepch.h"

#include "OpenGLVertexArray.h"
#include "OpenGLShader.h"
#include "GameEngine/Log.h"
#include "GameEngine/Core.h"
#include <glad/glad.h>

namespace GameEngine {
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::string& key, const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		GE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		// Make sure VertexArray and VertexBuffer are binded
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		// Set the layout of the VertexBuffer
		uint32_t index = 0;
		for (const auto& element : vertexBuffer->GetLayout()) // possible setting iterator methods
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				OpenGLShader::ShaderType2GlType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				vertexBuffer->GetLayout().GetStride(),
				(void*)(uintptr_t)element.Offset // to avoid "'type cast': conversion from 'const uint32_t' to 'void *' of greater size" warning
			);
			index++;
		}

		// Save VertexBuffer inside VertexArray
		m_VertexBuffers[key] = vertexBuffer;
	}

	void OpenGLVertexArray::AddIndexBuffer(const std::string& key,const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		// Make sure VertexArray and VertexBuffer are binded
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		// Save IndexBuffer inside VertexArray
		m_IndexBuffers[key] = indexBuffer;
	}

	const std::shared_ptr<VertexBuffer>& OpenGLVertexArray::GetVertexBuffer(const std::string& key) const
	{
		try
		{
			return m_VertexBuffers.at(key);
		}
		catch (std::out_of_range)
		{
			GE_CORE_ASSERT(false, "Couldn't find a IndexBuffer with the given key: \"" + key + '"');
			// This is a hack to avoid "warning returning address of local variable or temporary"
			static const std::shared_ptr<VertexBuffer> null = nullptr;
			return null;
		}
	}

	const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer(const std::string& key) const
	{
		try
		{
			return m_IndexBuffers.at(key);
		}
		catch (std::out_of_range)
		{
			GE_CORE_ASSERT(false, "Couldn't find a IndexBuffer with the given key: \""+key+'"');
			static const std::shared_ptr<IndexBuffer> null = nullptr;
			return null;
		}
	}
}