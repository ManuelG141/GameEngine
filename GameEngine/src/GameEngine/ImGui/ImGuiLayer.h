#pragma once

#include "GameEngine/Layer.h"


struct ImGuiContext;
struct ImGuiIO;

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
		float m_Time = 0.0f;
		ImGuiContext* m_Context = nullptr;
		ImGuiIO* m_Io;
		bool m_ShowDemo;
	};
}