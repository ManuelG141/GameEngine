#include "GameEngine.h"

#include "Examples/ChessBoard.h"
#include "Examples/Triangle.h"

#include "imgui/imgui.h"

class ExampleLayer : public GameEngine::Layer
{
public:
	ExampleLayer(const char* name = "Example")
		: Layer(name)
	{
		using namespace GameEngine; // Just on this scope
		// Draw a ChessBoard & Triangle for testing
		// 1. Chess Board 
		// Vertex Array
		m_VertexArrays["chess"].reset(VertexArray::Create());

		// Create Vertex Buffer and bind it
		std::shared_ptr<VertexBuffer> ChessBoardVB(VertexBuffer::Create(ChessBoard::vertices, sizeof(ChessBoard::vertices)));
		ChessBoardVB->Bind();

		// Set layout for VertexBuffer
		ChessBoardVB->SetLayout({
			{ShaderDataType::Float3, "a_Position"}
		});
		// Add VertexBuffer to the VertexArray
		m_VertexArrays["chess"]->AddVertexBuffer("board", ChessBoardVB);

		// Create Index buffer
		std::shared_ptr<IndexBuffer> ChessBoardWhiteIndicesIB(IndexBuffer::Create(ChessBoard::whiteIndices, ChessBoard::totalIndices));
		std::shared_ptr<IndexBuffer> ChessBoardBlackIndicesIB(IndexBuffer::Create(ChessBoard::blackIndices, ChessBoard::totalIndices));
		m_VertexArrays["chess"]->AddIndexBuffer("white", ChessBoardWhiteIndicesIB);
		m_VertexArrays["chess"]->AddIndexBuffer("black", ChessBoardBlackIndicesIB);

		// Create Shader class to use it later
		m_Shaders["white"].reset(Shader::Create(ChessBoard::vertexSrc, ChessBoard::whiteFragmentSrc));
		m_Shaders["black"].reset(Shader::Create(ChessBoard::vertexSrc, ChessBoard::blackFragmentSrc));

		m_VertexArrays["chess"]->UnBind();

		// 2. Triangle
		m_VertexArrays["triangle"].reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> TriangleVB(VertexBuffer::Create(Triangle::vertices, sizeof(Triangle::vertices)));
		TriangleVB->Bind();

		TriangleVB->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"}
			});
		m_VertexArrays["triangle"]->AddVertexBuffer("vertices+color", TriangleVB);

		std::shared_ptr<IndexBuffer> TriangleIB(IndexBuffer::Create(Triangle::indices, Triangle::totalIndices));
		m_VertexArrays["triangle"]->AddIndexBuffer("indices", TriangleIB);

		m_Shaders["triangle"].reset(Shader::Create(Triangle::vertexSrc, Triangle::fragmentSrc));
	}

	virtual void OnUpdate() override
	{
		m_Shaders["white"]->Bind();
		GameEngine::Renderer::Submit("white", m_VertexArrays["chess"]);

		m_Shaders["black"]->Bind();
		GameEngine::Renderer::Submit("black", m_VertexArrays["chess"]);

		m_Shaders["triangle"]->Bind();
		GameEngine::Renderer::Submit("indices", m_VertexArrays["triangle"]);

		//GE_INFO("[{0}] Layer::Update", m_DebugName);
		if (GameEngine::Input::IsKeyPressed(GE_KEY_TAB))
			GE_TRACE("TAB is pressed!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello world");
		ImGui::End();
	}

	virtual void OnEvent(GameEngine::Event& event) override
	{
		//GE_TRACE("[{0}]: {1}", m_DebugName, event.ToString());
	}
private:
	std::unordered_map<std::string, std::shared_ptr<GameEngine::VertexArray>> m_VertexArrays; // To store multiple VertexArrays
	std::unordered_map<std::string, std::shared_ptr<GameEngine::Shader>> m_Shaders; // To store multiple shaders
};

class Sandbox : public GameEngine::Application
{
public:
	Sandbox()
		// If you define the Application Constructor here you can change window properties
		// If you want to use the default options ("Game Engine", 1280U, 720U) just don't call the constructor of Application
		: Application(GameEngine::WindowProps("Sandbox", 720U, 720U))
	{
		// Disable/Enable VSync
		this->SetVSync(true);

		// Example of Layer Implementation
		PushLayer(new ExampleLayer());
	}

	~Sandbox() = default;
};

GameEngine::Application* GameEngine::CreateApplication()
{
	return new Sandbox();
}