#include "Engine.h"
/*
     Starlight 64, Project started 6/11/2024.
     Code written by: George Skaggs
*/

/*
    Simple application entry point. Since StartEngine will let the game engine
    take over the thread, we can just wait until that function finally ends to finish, which
    is when we would need to call the shutdown command, so it all works out!
*/
int main()
{
#pragma region initalizeVariables
    //NOTE: Once this engine is closer to being finished
    //This section will be refactered. For now this is what I'm doing
    //for easier testing.
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