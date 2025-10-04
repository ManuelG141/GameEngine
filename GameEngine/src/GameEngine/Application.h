#pragma once

#include "Core.h"
#include "Window.h"
#include "GameEngine/LayerStack.h"
#include "GameEngine/Events/Event.h"
#include "GameEngine/Events/ApplicationEvent.h"
#include "GameEngine/ImGui/ImGuiLayer.h"

namespace GameEngine {

	// dllexport is required to use this class in sandbox application
	class GE_API Application
	{
	public:
		Application(const WindowProps& props = WindowProps());
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		void SetVSync(bool enabled);

		inline Window& GetWindowObject() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance; // To make Application a singleton class
	};

	// To be defined in the client
	Application* CreateApplication();

}