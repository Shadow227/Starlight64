#include "vulkanRenderer.h"
#include <fstream>
#pragma once
class Engine
{
	//Member Vars
protected:
	Renderer m_graphicsEngine;
	GameScene* m_currScene = nullptr;
	SLE64_BuildData* m_gameData;
	//Public Engine Functions
public:
	/*
	First function that calls. This initalizes the Starlight64 engine and all subsystems.
	Returns 1 when the engine starts correctly, otherwise it will return a negitave error code.
	*/
	int InitalizeEngine(SLE64_BuildData* gameData);
	/*
	The starting point for the program. This will start all subsystems and can ONLY be called after
	the engine has been initalized. This will also start the gameLoop.
	*/
	void StartEngine();
	/*
	This is the final function that is called at the end of the games lifespan. It shutsdown all subsystems
	and clears up hanging memory. Returns true if everything shuts down correctly.
	*/
	bool Shutdown();
	/*
	 Creates a log file from file name. If no file name is passed it creates a default log file.
	*/
	void CreateLogFile(const char* fileName = "StarlightEngineLog.txt");
	/*
	Updats a log file by appending the logMsg to the end of the file. If no fileName is passed
	this writes to the default log file.
	WARNING: If you do not create the log file before hand, then this function will not restart your [filename].txt file!
	which can lead to massive file sizes and fill your harddrive.
	*/
	void UpdateLogFile(const char* logMsg, const char* fileName = "StarlightEngineLog.txt");
	/*
	Loads a game scene from a sceneId. If the scene is already loaded it will reload the current scene, otherwise this will
	unload the current scene and load in a new scene.
	*/
	bool LoadScene(size_t sceneId);

};

