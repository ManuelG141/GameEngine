#pragma once

#include "Core.h"
#include "Window.h"

#include "GameEngine/LayerStack.h"
#include "GameEngine/ImGui/ImGuiLayer.h"

#include "GameEngine/Events/Event.h"
#include "GameEngine/Events/ApplicationEvent.h"

#include "GameEngine/Core/Timestep.h"

namespace GameEngine {

	// dllexport is required to use this class in sandbox application
	class Application
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
		GE_API inline Window& GetWindowObject() { return *m_Window; }
		GE_API inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running;

		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance; // To make Application a singleton class
	};

	// To be defined in the client
	Application* CreateApplication();

}