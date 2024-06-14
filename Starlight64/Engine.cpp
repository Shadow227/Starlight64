#include "Engine.h"


int Engine::InitalizeEngine(SLE64_BuildData* gameData)
{
    //Create log file, or clear log file if it already existed.
    CreateLogFile();
\
    UpdateLogFile("Initalizing Graphics Engine. . .");
    //Set our gameData
    m_gameData = gameData;
#pragma region GraphicsInit
    //Initalize the graphicsEngine
    int result = m_graphicsEngine.initalizeRenderer(m_gameData);
    //Check result and return error code if result was not a 1.
    if (result != 1)
        return result;
#pragma endregion
    UpdateLogFile("Init of Engine FINISHED!");
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
    if(m_currScene)
        m_currScene->DestroyScene();
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

bool Engine::LoadScene(size_t sceneId)
{
    GameSceneData* data = m_gameData->scenes[sceneId];
    if (data->isLoaded) 
    {
        //reload scene
    }
    else 
    {
        //Create our scene pointer using our data.
        GameScene* scene = GameScene::CreateScene(data);
        //Make sure the scene is initalized correctly
        if(scene)
        {
            //Destory our last loaded scene, clear the pointer and reassign it to our newly created scene.
            m_currScene->DestroyScene();
            delete m_currScene;
            m_currScene = scene;
        }
        else
        {
            UpdateLogFile("Error, Could not create or load scene!");
            return false;
        }
    }
    return true;
}
