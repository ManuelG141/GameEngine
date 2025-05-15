#include "gepch.h"

#include "GLFW/glfw3.h"
#include "imgui.h"
#include "Platform/OpenGL/imgui_impl_glfw.h"
#include "Platform/OpenGL/imgui_impl_opengl3.h"

#include "GameEngine/Window.h"
#include "GameEngine/Core.h"
#include "GameEngine/Log.h"
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
		ImGui_ImplGlfw_InitForOpenGL(GLFWwindow, false);

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
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<WindowResizeEvent>(GE_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
		dispatcher.Dispatch<WindowCloseEvent>(GE_BIND_EVENT_FN(ImGuiLayer::OnWindowCloseEvent));
		dispatcher.Dispatch<KeyPressedEvent>(GE_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(GE_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(GE_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(GE_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(GE_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<MouseButtonPressedEvent>(GE_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(GE_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		m_Io->DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		m_Io->DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}

	bool ImGuiLayer::OnWindowCloseEvent(WindowCloseEvent& e)
	{
		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		GLFWwindow* GLFWwindow = Application::Get().GetWindowObject().GetGLFWwindow();
		ImGuiKey imgui_key = ImGui_ImplGlfw_KeyToImGuiKey(e.GetKeyCode(), e.GetScanCode());

		ImGui_ImplGlfw_UpdateKeyModifiers(GLFWwindow);

		m_Io->AddKeyEvent(imgui_key, true);
		m_Io->SetKeyEventNativeData(imgui_key, e.GetKeyCode(), e.GetScanCode());
		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		GLFWwindow* GLFWwindow = Application::Get().GetWindowObject().GetGLFWwindow();
		ImGuiKey imgui_key = ImGui_ImplGlfw_KeyToImGuiKey(e.GetKeyCode(), e.GetScanCode());

		ImGui_ImplGlfw_UpdateKeyModifiers(GLFWwindow);

		m_Io->AddKeyEvent(imgui_key, false);
		m_Io->SetKeyEventNativeData(imgui_key, e.GetKeyCode(), e.GetScanCode());
		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		unsigned int codepoint = e.GetKeyCode();
		m_Io->AddInputCharacter(codepoint);
		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		m_Io->AddMousePosEvent(e.GetX(), e.GetY());
		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		m_Io->AddMouseWheelEvent(e.GetXOffset(), e.GetYOffset());
		return false;
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		m_Io->AddMouseButtonEvent(e.GetMouseButton(), true);
		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		m_Io->AddMouseButtonEvent(e.GetMouseButton(), false);
		return false;
	}
}