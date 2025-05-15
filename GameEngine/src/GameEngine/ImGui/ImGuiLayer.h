#pragma once

#include "GameEngine/Layer.h"

#include "GameEngine/Events/ApplicationEvent.h"
#include "GameEngine/Events/KeyEvent.h"
#include "GameEngine/Events/MouseEvent.h"

struct ImGuiContext;
struct ImGuiIO;

enum ImGuiKey;

ImGuiKey ImGui_ImplGlfw_KeyToImGuiKey(int keycode, int scancode);
void ImGui_ImplGlfw_UpdateKeyModifiers(GLFWwindow* window);

namespace GameEngine {

	class GE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(bool showDemo = true);
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;
	private:
		// Application Events
		bool OnWindowResizeEvent(WindowResizeEvent& e);
		bool OnWindowCloseEvent(WindowCloseEvent& e);

		// Key Events
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);

		// Mouse Events
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
	private:
		float m_Time = 0.0f;
		ImGuiContext* m_Context = nullptr;
		ImGuiIO* m_Io = nullptr;
		bool m_ShowDemo;
	};
}