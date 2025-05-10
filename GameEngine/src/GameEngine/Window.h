#pragma once

#include "gepch.h"

#include "GameEngine/Core.h"
#include "GameEngine/Events/Event.h"

namespace GameEngine {

	struct WindowProps
	{
		std::string Title;
		unsigned int Width, Height;

		WindowProps(const std::string& title = "Game Engine",
					unsigned int width = 1280U,
					unsigned int height = 720U)
			: Title(title), Width(width), Height(height) {}
	};

	// Interface representing a desktop system based Window
	// This should be implemented per platform.
	class GE_API Window
	{
	public:
		using EventCallBackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallBack(const EventCallBackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props);
	};
}