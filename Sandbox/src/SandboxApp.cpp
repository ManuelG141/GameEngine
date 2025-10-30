#include "GameEngine.h"

#include "Examples/ChessBoard.h"
#include "Examples/Triangle.h"

#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public GameEngine::Layer
{
public:
	ExampleLayer(const char* name = "Example", const bool vsync = true)
		: Layer(name), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_BoardPosition(0.0f), m_Vsync(vsync)
	{
		// Draw a ChessBoard & Triangle for testing
		// 1. Chess Board 
		// Vertex Array
		m_VertexArrays["chess"].reset(GameEngine::VertexArray::Create());

		// Create Vertex Buffer and bind it
		std::shared_ptr<GameEngine::VertexBuffer> ChessBoardVB(GameEngine::VertexBuffer::Create(ChessBoard::vertices, sizeof(ChessBoard::vertices)));
		ChessBoardVB->Bind();

		// Set layout for VertexBuffer
		ChessBoardVB->SetLayout({
			{GameEngine::ShaderDataType::Float3, "a_Position"}
		});
		// Add VertexBuffer to the VertexArray
		m_VertexArrays["chess"]->AddVertexBuffer("board", ChessBoardVB);

		// Create Index buffer
		std::shared_ptr<GameEngine::IndexBuffer> ChessBoardWhiteIB(GameEngine::IndexBuffer::Create(ChessBoard::whiteIndices, ChessBoard::totalIndices));
		std::shared_ptr<GameEngine::IndexBuffer> ChessBoardBlackIB(GameEngine::IndexBuffer::Create(ChessBoard::blackIndices, ChessBoard::totalIndices));
		m_VertexArrays["chess"]->AddIndexBuffer("white", ChessBoardWhiteIB);
		m_VertexArrays["chess"]->AddIndexBuffer("black", ChessBoardBlackIB);

		// Create Shader class to use it later
		m_Shaders["white"].reset(GameEngine::Shader::Create(ChessBoard::vertexSrc, ChessBoard::whiteFragmentSrc));
		m_Shaders["black"].reset(GameEngine::Shader::Create(ChessBoard::vertexSrc, ChessBoard::blackFragmentSrc));

		m_VertexArrays["chess"]->UnBind();

		// 2. Triangle
		m_VertexArrays["triangle"].reset(GameEngine::VertexArray::Create());

		std::shared_ptr<GameEngine::VertexBuffer> TriangleVB(GameEngine::VertexBuffer::Create(Triangle::vertices, sizeof(Triangle::vertices)));
		TriangleVB->Bind();

		TriangleVB->SetLayout({
			{GameEngine::ShaderDataType::Float3, "a_Position"},
			{GameEngine::ShaderDataType::Float4, "a_Color"}
			});
		m_VertexArrays["triangle"]->AddVertexBuffer("vertices+color", TriangleVB);

		std::shared_ptr<GameEngine::IndexBuffer> TriangleIB(GameEngine::IndexBuffer::Create(Triangle::indices, Triangle::totalIndices));
		m_VertexArrays["triangle"]->AddIndexBuffer("indices", TriangleIB);

		m_Shaders["triangle"].reset(GameEngine::Shader::Create(Triangle::vertexSrc, Triangle::fragmentSrc));
	}

	virtual void OnUpdate(const GameEngine::Timestep& ts) override
	{
		GE_TRACE("Delta time ({0}ms)", ts.GetMilliSeconds());

		// More smooth with polling than with key events
		if (GameEngine::Input::IsKeyPressed(GE_KEY_R))
		{
			if (GameEngine::Input::IsKeyPressed(GE_KEY_W))
				// Speed = units/frame, ts = frame/seconds, Speed * ts = units/seconds (Frame agnostic)
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (GameEngine::Input::IsKeyPressed(GE_KEY_S))
				m_CameraRotation -= m_CameraRotationSpeed * ts;
		}
		else
		{
			if (GameEngine::Input::IsKeyPressed(GE_KEY_W))
				m_CameraPosition.y += m_CameraMoveSpeed * ts;
			if (GameEngine::Input::IsKeyPressed(GE_KEY_S))
				m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		}

		if (GameEngine::Input::IsKeyPressed(GE_KEY_A))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		if (GameEngine::Input::IsKeyPressed(GE_KEY_D))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		GameEngine::RenderCommand::SetClearColor({
			235.f / 255.f,
			24.f / 255.f,
			106.f / 255.f,
			1.0f
		});
		GameEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		GameEngine::Renderer::BeginScene(m_Camera);

		// Just a brief demonstration (not optimal)
		static glm::mat4 scaleMatrix = glm::mat4(1.0f);
		scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(m_BoardScale));

		for (int i = 0; i < m_BoardWidth * m_BoardWidth; i++) // Single loop that behaves like a nested loop
		{
			const int x = i / m_BoardWidth;
			const int y = i % m_BoardWidth;
			glm::vec3 pos(
				m_BoardPosition.x + x * (m_BoardScale * 1.1f),
				m_BoardPosition.y + y * (m_BoardScale * 1.1f),
				m_BoardPosition.z + 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scaleMatrix;
			GameEngine::Renderer::Submit(m_Shaders["white"], "white", m_VertexArrays["chess"], transform);
			GameEngine::Renderer::Submit(m_Shaders["black"], "black", m_VertexArrays["chess"], transform);
		}

		GameEngine::Renderer::Submit(m_Shaders["triangle"], "indices", m_VertexArrays["triangle"]);

		GameEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Camera");
		ImGui::Text("Use \"W A S D\" to move the camera around the scene, use \"W S\" with \"R\" pressed to rotate the camera");

		ImGui::SliderFloat("linear speed (units/s)", &m_CameraMoveSpeed, 0.f, 10.0f);
		ImGui::SliderFloat("angular speed (degrees/s)", &m_CameraRotationSpeed, 0.f, 90.0f);

		ImGui::SliderFloat3("Board position", &m_BoardPosition.x, -2.0f, 2.0f);
		ImGui::SliderFloat("Board scale", &m_BoardScale, 0.01f, 1.0f);
		ImGui::SliderInt("Board grid width", &m_BoardWidth, 1, 50);

		if (ImGui::Button(m_Vsync ? "Vsync (On)" : "Vsync (Off)"))
		{
			m_Vsync = !m_Vsync;
			GameEngine::Application::Get().SetVSync(m_Vsync);
		}

		if (ImGui::Button("Reset board"))
			m_BoardPosition = { 0.0f, 0.0f, 0.0f };

		if (ImGui::Button("Reset camera"))
		{
			m_CameraPosition = {0.0f, 0.0f, 0.0f};
			m_CameraRotation = 0.f;
		}

		ImGui::End();
	}

	virtual void OnEvent(GameEngine::Event& event) override
	{
		//GE_TRACE("[{0}]: {1}", m_DebugName, event.ToString());
		GameEngine::EventDispatcher dispatcher(event);
	}
private:
	std::unordered_map<std::string, std::shared_ptr<GameEngine::VertexArray>> m_VertexArrays; // To store multiple VertexArrays
	std::unordered_map<std::string, std::shared_ptr<GameEngine::Shader>> m_Shaders; // To store multiple shaders

	float m_CameraMoveSpeed = 1.5f; // Units/seconds (Thanks to timestep implementation)
	float m_CameraRotationSpeed = 45.0f; // Degrees/seconds

	float m_CameraRotation = 0.0f;
	glm::vec3 m_CameraPosition;
	GameEngine::OrthographicCamera m_Camera;

	glm::vec2 m_BoardMoveSpeed = { 1.0f, 1.0f };
	glm::vec3 m_BoardPosition;
	int m_BoardWidth = 5;
	float m_BoardScale = 0.1f;

	bool m_Vsync;
};

class Sandbox : public GameEngine::Application
{
public:
	Sandbox()
		// If you define the Application Constructor here you can change window properties
		// If you want to use the default options ("Game Engine", 1280U, 720U) just don't call the constructor of Application
		: Application(GameEngine::WindowProps("Sandbox", 1280U, 720U))
	{
		const bool EnableVsync = true;

		// Disable/Enable VSync
		this->SetVSync(EnableVsync);

		// Example of Layer Implementation
		PushLayer(new ExampleLayer("Example", EnableVsync));
	}

	~Sandbox() = default;
};

GameEngine::Application* GameEngine::CreateApplication()
{
	return new Sandbox();
}