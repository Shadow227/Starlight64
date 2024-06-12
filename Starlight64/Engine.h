#include "vulkanRenderer.h"
#include <fstream>
#pragma once
class Engine
{
	//Member Vars
protected:
	Renderer m_graphicsEngine;
	//Public Engine Functions
public:
	//Starts all core parts needed for STARLIGHT 64 to work, Returns 1 if the engine starts without any issue,
	//otherwise it returns the error code reached.
	int InitalizeEngine(SLE64_BuildData* gameData);
	//Public function to start the engine tick, Handles the starting functions for all subsystems.
	//This function will only return after all code is ready for shutdown, as it will start the game loop
	void StartEngine();
	//Cleans up memory and shuts down all systems to allow graceful shutdown.
	bool Shutdown();
	//Create's a log file based on a file name. You can leave the fileName blank to use the
	//default log file.
	void CreateLogFile(const char* fileName = "StarlightEngineLog.txt");
	//Adds the value of "logMsg" to the Log File.
	void UpdateLogFile(const char* logMsg, const char* fileName = "StarlightEngineLog.txt");

};

