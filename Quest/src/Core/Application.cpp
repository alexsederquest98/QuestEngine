#include "qepch.h"
#include "Application.h"
#include "Debug/Profiler.h"
#include "Utility/Timer.h"

#include "InputManager.h"

#include <thread>
#include <chrono>

namespace Quest
{
	Ref<EventManager> Application::s_EventManager = CreateRef<EventManager>();

	bool Application::s_Instantiated = false;
	Application* Application::s_Instance = nullptr;

	Application::Application(ApplicationSpecification spec)
	{
		QE_CORE_ASSERT_MSG(!s_Instantiated, "Only 1 Application class may be used.");
		s_Instantiated = true;
		s_Instance = this;

		m_Window = Window::Create(WindowSpecification(spec.AppName));
		m_Window->SetEventCallback(QE_BIND_EVENT_FUNC(OnEvent));

		m_GraphicsDevice = GraphicsDevice::Create({.window = m_Window });

		s_EventManager->Subscribe(EventType::MouseMoved, QE_BIND_EVENT_FUNC(OnMouseMoved));
		s_EventManager->Subscribe(EventType::WindowClose, QE_BIND_EVENT_FUNC(OnWindowClose));
		s_EventManager->Subscribe(EventType::KeyPressed, QE_BIND_EVENT_FUNC(OnKeyPress));
		s_EventManager->Subscribe(EventType::WindowResize, QE_BIND_EVENT_FUNC(OnWindowResize));

		QE_CORE_CRITICAL("Application Initialized");
	}

	Application::~Application()
	{
		s_Instantiated = false;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			// Frame timing
			Timestep currentTime = m_Window->GetTime();
			Timestep deltaTime = currentTime - m_LastFrameTime;
			m_LastFrameTime = currentTime;

			// Update window title
			m_Window->SetTitle(std::to_string((int)(1.0 / deltaTime)));

			// Poll window events (input)
			m_Window->OnUpdate();

			// Draw frame
			m_GraphicsDevice->DrawFrame();

			// limiting updates/sec for testing for now
			//std::this_thread::sleep_for(std::chrono::milliseconds(15));
		}

		// Make sure all work on the gpu is finished before deleting objects
		m_GraphicsDevice->WaitForDeviceToFinishExecuting();
	}

	void Application::OnEvent(Event& e)
	{
	}

	void Application::OnWindowClose(Event& e)
	{
		//WindowCloseEvent event = dynamic_cast<WindowCloseEvent&>(e);
		//QE_CORE_DEBUG("{0}", e.ToString());
		m_Running = false;
	}

	void Application::OnMouseMoved(Event& e)
	{
		//MouseMovedEvent event = dynamic_cast<MouseMovedEvent&>(e);
		//QE_CORE_DEBUG("{0}, {1}", event.GetX(), event.GetY());
		//QE_CORE_DEBUG("{0}", e.ToString());
	}

	void Application::OnKeyPress(Event& e)
	{
		QE_CORE_DEBUG("{0}", e.ToString());
		
		if (InputManager::IsKeyPressed(Key::Escape))
			Close();
	}

	void Application::OnWindowResize(Event& e)
	{
		WindowResizeEvent event = static_cast<WindowResizeEvent&>(e);
		if (event.GetWidth() == 0 || event.GetHeight() == 0)
			m_Window->PauseWindow();

		m_GraphicsDevice->FramebufferResize();
	}

	void Application::Close()
	{
		m_Running = false;
	}

}