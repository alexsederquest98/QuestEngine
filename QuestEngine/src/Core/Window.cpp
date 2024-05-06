#include "QuestCommon.h"
#include "Window.h"

#include <GLFW/glfw3.h>

namespace Quest
{
	// GLFW error function
	static void GLFWerrorCallback(int error, const char* description)
	{
		QE_CORE_ERROR_TAG("Window", "GLFW Error: ({0}): {1}", error, description);
	}

	Window::Window(Window::CreateInfo ci)
	{
		QE_CORE_DEBUG_TAG("Window", "Creating Window: {0} - ({1}, {2})", ci.Title, ci.Width, ci.Height);

		m_WindowData.m_Title = ci.Title;
		m_WindowData.m_Width = ci.Width;
		m_WindowData.m_Height = ci.Height;
		m_WindowData.m_VSync = false;

		// Init GLFW
		int glfwSuccess = glfwInit();
		QE_CORE_VERIFY(glfwSuccess, "Failed to initialize GLFW :(");

		glfwSetErrorCallback(GLFWerrorCallback);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Vulkan only supported for now

		m_Window = glfwCreateWindow((int)m_WindowData.m_Width, (int)m_WindowData.m_Height, m_WindowData.m_Title.c_str(), nullptr, nullptr);

		glfwSetWindowUserPointer(m_Window, &m_WindowData);

		// Callbacks
		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{

			}
		);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{

			}
		);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{

			}
		);

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{

			}
		);

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{

			}
		);

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{

			}
		);

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{

			}
		);

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{

			}
		);
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	const std::string Window::GetTitle()
	{
		return m_WindowData.m_Title;
	}

	const uint32 Window::GetWidth()
	{
		return m_WindowData.m_Width;
	}

	const uint32 Window::GetHeight()
	{
		return m_WindowData.m_Height;
	}

	GLFWwindow* Window::GetNativeWindow()
	{
		return m_Window;
	}

	void Window::ProcessEvents()
	{
		glfwPollEvents();
	}

	void Window::SwapBuffers()
	{
		//glfwSwapBuffers(m_Window); // wont do anything for vulkan but whatever
	}

	void Window::PauseWindow()
	{
		int width = 0, height = 0;
		glfwGetFramebufferSize(m_Window, &width, &height);
		while (width == 0 || height == 0)
		{
			glfwGetFramebufferSize(m_Window, &width, &height);
			glfwWaitEvents();
		}
	}
}