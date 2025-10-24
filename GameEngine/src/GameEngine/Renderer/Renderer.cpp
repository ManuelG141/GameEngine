#include "gepch.h"
#include "Renderer.h"

namespace GameEngine {

	// Not implemented for now
	void Renderer::BeginScene() {}
	void Renderer::EndScene() {}

	void Renderer::Submit(const std::string& key, const std::shared_ptr<VertexArray>& vertexArray)
	{
		// Make sure VertexArray and IndexBuffer are binded
		vertexArray->Bind();
		vertexArray->GetIndexBuffer(key)->Bind();
		// Make the draw call
		RenderCommand::DrawIndexed(key, vertexArray);
	}
}