#include "Application.h"

#include <iostream>

namespace Quest
{
	Application::Application()
	{
		std::cout << "Application::Application\n";
	}

	Application::~Application() noexcept
	{
		std::cout << "Application::~Application\n";
	}

	void Application::Test()
	{
		std::cout << "Application::Test is successful\n";
	}
}