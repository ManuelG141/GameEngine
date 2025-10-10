#pragma once

#include "gepch.h"

namespace GameEngine {

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetSize() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetCount() const = 0; // Num of indices
		virtual uint32_t GetSize() const = 0; // Size of indices in bytes

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};
}