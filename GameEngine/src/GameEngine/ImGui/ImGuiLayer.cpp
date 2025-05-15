#include "gepch.h"

#include "GameEngine/Log.h"

#include "GLFW/glfw3.h"
#include "imgui.h"
#include "Platform/OpenGL/imgui_impl_glfw.h"
#include "Platform/OpenGL/imgui_impl_opengl3.h"

#include "ImGuiLayer.h"
#include "GameEngine/Application.h"
#include "Platform/Windows/WindowsWindow.h"


namespace GameEngine {

	ImGuiLayer::ImGuiLayer(bool showDemo)
		: Layer("ImGuiLayer"), m_ShowDemo(showDemo)
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnAttach()
	{
		GE_CORE_WARN("Initializing Dear ImGui!");
		IMGUI_CHECKVERSION();
		m_Context = ImGui::CreateContext();
		//ImGui::SetCurrentContext(m_Context);
		//ImGui::SetAllocatorFunctions();
		m_Io = &ImGui::GetIO();
		m_Io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		m_Io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		GLFWwindow* GLFWwindow = Application::Get().GetWindowObject().GetGLFWwindow();
		ImGui_ImplGlfw_InitForOpenGL(GLFWwindow, true);

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext(m_Context);
	}

	void ImGuiLayer::OnUpdate()
	{
		Application& app = Application::Get();
		m_Io->DisplaySize = ImVec2(app.GetWindowObject().GetWidth(), app.GetWindowObject().GetHeight());

		float time = (float)glfwGetTime();
		m_Io->DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (m_ShowDemo)
			ImGui::ShowDemoWindow(&m_ShowDemo);

		// Rendering
		ImGui::Render();
		ImGui::EndFrame();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		GE_TRACE("[{0}]: {1}", m_DebugName, event.ToString());
	}
}