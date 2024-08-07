#pragma once

#include "Core/Common.h"

#include <memory>

namespace QE
{
	/*
	* This is the main class that clients will subclass
	* Setup game specific services in the Init() function
	* Put your update code in the OnTick() function
	* Any ImGui code should go in the OnImGuiRender() function
	**/
	class Application
	{
	public:
		Application();
		virtual ~Application() noexcept;

		//virtual void Init() = 0;
		//virtual void Shutdown() = 0;
		virtual void OnTick() = 0;
		//virtual void OnImGuiRender() = 0;
	};
}

extern std::unique_ptr<QE::Application> CreateApplication();
