#pragma once

#include <string>

#include "Base.h"
#include "Window.h"
#include "Timestep.h"
#include "Events/EventManager.h"
#include "Renderer/GraphicsDevice.h"

// This forward dec of main is so that I can set it as a friend to the Application class.
// Since main is a friend, I can call the private Run() function from main and only main.
int main(int argc, char** argv);

namespace Quest
{
	class Application
	{
	public:
		struct ApplicationSpecification
		{
			std::string AppName;
			int ArgCount = 0;
			char** Arguments = nullptr;

			// Allow indexing the struct to get arguments
			const char* operator[](int index) const
			{
				QE_CORE_ASSERT(index < ArgCount);
				return Arguments[index];
			}
		};

		Application(ApplicationSpecification spec);
		virtual ~Application();

		Window& GetWindow() { return *m_Window; }
		static Application& Get() { return *s_Instance; }
		static Ref<EventManager> GetEventManager() { return s_EventManager; }

		void OnEvent(Event& e);
		void OnWindowClose(Event& e);
		void OnMouseMoved(Event& e);
		void OnKeyPress(Event& e);
		void OnWindowResize(Event& e);

		void Close();
	private:
		void Run();
	private:
		Ref<Window> m_Window;
		bool m_Running = true;

		Scope<GraphicsDevice> m_GraphicsDevice;

		static Ref<EventManager> s_EventManager;

		Timestep m_LastFrameTime = 0.0f;

		// Only allow 1 application to exist
		static bool s_Instantiated;
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// Defined in the client
	Scope<Application> CreateApplication(Application::ApplicationSpecification spec);
}