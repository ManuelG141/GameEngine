#include "GameEngine.h"
#include "imgui/imgui.h"

class ExampleLayer : public GameEngine::Layer
{
public:
	ExampleLayer(const char* name = "Example")
		: Layer(name) {}

	virtual void OnUpdate() override
	{
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

	~Sandbox()
	{

	}
};

GameEngine::Application* GameEngine::CreateApplication()
{
	return new Sandbox();
}