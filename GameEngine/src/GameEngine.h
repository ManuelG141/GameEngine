#pragma once

// Only for client applications
#include "GameEngine/Application.h"
#include "GameEngine/Window.h"

// Layer System
#include "GameEngine/Layer.h"
#include "GameEngine/ImGui/ImGuiLayer.h"

#include "GameEngine/Core/Timestep.h"

// Input polling stuff
#include "GameEngine/Input.h"
#include "GameEngine/KeyCodes.h"
#include "GameEngine/MouseButtonCodes.h"

// Event System stuff
#include "GameEngine/Events/ApplicationEvent.h"
#include "GameEngine/Events/KeyEvent.h"
#include "GameEngine/Events/MouseEvent.h"
#include "GameEngine/Events/Event.h"

// Renderer Stuff
#include "GameEngine/Renderer/Renderer.h"
#include "GameEngine/Renderer/Buffer.h"
#include "GameEngine/Renderer/Shader.h"
#include "GameEngine/Renderer/Camera.h"

#include "GameEngine/Log.h"

// -- Entry Point -----------------------------
#include "GameEngine/EntryPoint.h"
// --------------------------------------------