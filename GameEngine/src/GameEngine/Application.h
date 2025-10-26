#pragma once

#include "Core.h"
#include "Window.h"
#include "GameEngine/LayerStack.h"
#include "GameEngine/Events/Event.h"
#include "GameEngine/Events/ApplicationEvent.h"
#include "GameEngine/ImGui/ImGuiLayer.h"
#include "GameEngine/Renderer/Shader.h"
#include "GameEngine/Renderer/Buffer.h"
#include "GameEngine/Renderer/VertexArray.h"
#include "GameEngine/Renderer/Camera.h"

namespace GameEngine {

	// dllexport is required to use this class in sandbox application
	class GE_API Application
	{
	public:
		GE_API Application(const WindowProps& props = WindowProps());
		GE_API virtual ~Application();

		GE_API void Run();

		GE_API void OnEvent(Event& e);

		GE_API void PushLayer(Layer* layer);
		GE_API void PushOverlay(Layer* overlay);
		GE_API void PopLayer(Layer* layer);
		GE_API void PopOverlay(Layer* overlay);

		GE_API void SetVSync(bool enabled);
		GE_API inline OrthographicCamera& GetOrthographicCamera() { return m_Camera; }
		GE_API inline Window& GetWindowObject() { return *m_Window; }
		GE_API inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running;
		LayerStack m_LayerStack;

		OrthographicCamera m_Camera;
	private:
		static Application* s_Instance; // To make Application a singleton class
	};

	// To be defined in the client
	Application* CreateApplication();

}