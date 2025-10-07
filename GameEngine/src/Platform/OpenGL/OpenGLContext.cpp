#include "gepch.h"
#include "OpenGLContext.h"
#include "GameEngine/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace GameEngine {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		GE_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);

		// glad documentation: https://github.com/Dav1dde/glad
		// Initialize glad with glfw context
		GE_CORE_WARN("Initializing glad!");
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GE_CORE_ASSERT(status, "Failed to initilize Glad!");
		GE_CORE_INFO("Glad has been successfully initialized!");

		GE_CORE_INFO("OpenGL Info:");
		GE_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		GE_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		GE_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle); // https://www.glfw.org/docs/latest/window_guide.html#buffer_swap
	}
}