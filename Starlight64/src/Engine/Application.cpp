#include "Application.h"

namespace SLE 
{
	Application::Application()
	{
	}
	Application::~Application()
	{
	}
	void Application::startApp(const char* applicationName, int windowHeight, int windowWidth, const char* levelFiles)
	{
		Engine game;
		
		SLE64_BuildData buildData;
		buildData.gameName = applicationName;
		SLE64_WINData window;
		window.windowHeight = windowHeight;
		window.windowWidth = windowWidth;
		buildData.windowData = &window;

		//TODO: Make level exporter and read in levelBuild file here.

		game.InitalizeEngine(&buildData);
		game.StartEngine();
		game.Shutdown();
	}
}