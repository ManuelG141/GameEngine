#include "gepch.h"
#include "Renderer.h"

namespace GameEngine {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(const OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	
	// Not implemented for now
	void Renderer::EndScene() {}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::string& indexBufferkey, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		// Bind shader first
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix); // Camera
		shader->UploadUniformMat4("u_Transform", transform); // Model

		// Make sure VertexArray and IndexBuffer are binded
		vertexArray->Bind();
		vertexArray->GetIndexBuffer(indexBufferkey)->Bind();
		// Make the draw call
		RenderCommand::DrawIndexed(indexBufferkey, vertexArray);
	}
}