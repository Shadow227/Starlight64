#include <engine.h>

int main() 
{
#pragma region initalizeVariables
    Engine gameEngine;
    SLE64_WINData winData;
    winData.windowHeight = 1280;
    winData.windowWidth = 720;
    SLE64_BuildData gameData;
    gameData.gameName = "Collectathon 64 | SLE64";
    gameData.windowData = &winData;
#pragma endregion
    int result = gameEngine.InitalizeEngine(&gameData);
    if (result != 1)
        return result;
    gameEngine.StartEngine();
    gameEngine.Shutdown();
    return 1;
}