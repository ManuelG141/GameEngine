#include "gepch.h"
#include "OpenGLBuffer.h"
#include "GameEngine/Log.h"

#include <glad/glad.h>

namespace GameEngine {

	////////////////////////////////////////////////////////////////////////////
	// Vertex Buffer methods //////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
		: m_Size(size)
	{
		glCreateBuffers(1, &m_RendererID);
		this->Bind();
		glBufferData(GL_ARRAY_BUFFER, this->GetSize(), vertices, GL_STATIC_DRAW); // Hardcoded to static draw for now
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	////////////////////////////////////////////////////////////////////////////
	// Index Buffer methods ///////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		glCreateBuffers(1, &m_RendererID);
		this->Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->GetSize(), indices, GL_STATIC_DRAW); // Hardcoded to static draw for now
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}