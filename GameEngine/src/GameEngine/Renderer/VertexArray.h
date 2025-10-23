#pragma once

#include "GameEngine/Renderer/Buffer.h"

namespace GameEngine {

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void AddVertexBuffer(const std::string& key, const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void AddIndexBuffer(const std::string& key, const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual const std::unordered_map<std::string, std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const std::unordered_map<std::string, std::shared_ptr<IndexBuffer>>& GetIndexBuffers() const = 0;
		virtual const std::shared_ptr<VertexBuffer>& GetVertexBuffer(const std::string& key) const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer(const std::string& key) const = 0;

		static VertexArray* Create();
	};

}