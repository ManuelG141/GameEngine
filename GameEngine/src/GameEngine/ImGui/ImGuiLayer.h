#pragma once

#include "GameEngine/Layer.h"

#include "GameEngine/Events/ApplicationEvent.h"
#include "GameEngine/Events/KeyEvent.h"
#include "GameEngine/Events/MouseEvent.h"

struct ImGuiContext; // Dear ImGui context (opaque structure, unless including imgui_internal.h)
struct ImGuiIO;      // Main configuration and I/O between your application and ImGui (also see: ImGuiPlatformIO)

namespace GameEngine {

	class GE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(bool showDemo = true);
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
		ImGuiContext* m_Context = nullptr;
		ImGuiIO* m_Io = nullptr;
		bool m_ShowDemo;
		static constexpr const char* s_Glsl_version = "#version 410";
	};
}