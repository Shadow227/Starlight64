#include "Engine.h"

int Engine::InitalizeEngine()
{
    CreateLogFile();
    UpdateLogFile("Initalizing Graphics Engine. . .");
#pragma region GraphicsInit
    //Initalize the graphicsEngine

    int result = m_graphicsEngine.initalizeRenderer();
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
    return false;
}

void Engine::CreateLogFile(const char* fileName)
{
    //create file stream
    std::ofstream file;
    //open file
    file.open(fileName, std::ios::app | std::ios::out);
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
