#include "gepch.h"
#include "Renderer.h"

namespace GameEngine {

	// In the future it will be possible to change Graphics API at runtime
	RendererAPI Renderer::s_RendererAPI = RendererAPI::OpenGL;
}