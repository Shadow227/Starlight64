#pragma once
#include "Engine.h"
namespace SLE
{
	class SLE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void startApp(const char* applicationName, int windowWidth, int windowHeight, const char* levelFiles);
		
	};

	Application* CreateApp();
}


