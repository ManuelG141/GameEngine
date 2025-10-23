#pragma once

#include "GameEngine/Renderer/VertexArray.h"

namespace GameEngine {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void AddVertexBuffer(const std::string& key, const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void AddIndexBuffer(const std::string& key, const std::shared_ptr<IndexBuffer>& indexBuffer) override;
	
		virtual const std::unordered_map<std::string, std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
		virtual const std::unordered_map<std::string, std::shared_ptr<IndexBuffer>>& GetIndexBuffers() const override { return m_IndexBuffers; }
		virtual const std::shared_ptr<VertexBuffer>& GetVertexBuffer(const std::string& key) const override;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer(const std::string& key) const override;
	private:
		uint32_t m_RendererID = 0;
		std::unordered_map<std::string, std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::unordered_map<std::string, std::shared_ptr<IndexBuffer>> m_IndexBuffers;
	};

}