#pragma once

#include "GameEngine/Core.h"
#include "GameEngine/Events/Event.h"

namespace GameEngine 
{

	class Layer
	{
	public:
		GE_API Layer(const std::string& name = "Layer");
		GE_API virtual ~Layer();

		GE_API virtual void OnAttach() {}
		GE_API virtual void OnDetach() {}
		GE_API virtual void OnUpdate() {}
		GE_API virtual void OnImGuiRender() {}
		GE_API virtual void OnEvent(Event& event) {}

		GE_API inline std::string& GetName() { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}