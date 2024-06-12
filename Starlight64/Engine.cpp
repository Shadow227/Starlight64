#include "Engine.h"

int Engine::InitalizeEngine(SLE64_BuildData* gameData)
{
    CreateLogFile();
    UpdateLogFile("Initalizing Graphics Engine. . .");
#pragma region GraphicsInit
    //Initalize the graphicsEngine

    int result = m_graphicsEngine.initalizeRenderer(gameData);
    //Check result and return error code if result was not a 1.
    if (result != 1)
        return result;
#pragma endregion
    UpdateLogFile("Initalization of Engine FINISHED!");
    return 1;
}

void Engine::StartEngine()
{
    //TEMP
    m_graphicsEngine.graphicsUpdate();
}

bool Engine::Shutdown()
{
    m_graphicsEngine.Shutdown();
    return true;
}

void Engine::CreateLogFile(const char* fileName)
{
    //create file stream
    std::ofstream file;
    //open file
    file.open(fileName, std::ios::trunc | std::ios::out);
    //Check if file opened
    if (file.is_open()) 
    {
        file << "Start of Starlight Engine Log:" << std::endl;
        file.close();
    }
}

void Engine::UpdateLogFile(const char* logMsg, const char* fileName)
{
    //create file stream
    std::ofstream file;
    //open file
    file.open(fileName, std::ios::app | std::ios::out);
    //Check if file opened
    if (file.is_open())
    {
        file << logMsg << std::endl;
        file.close();
    }
}
