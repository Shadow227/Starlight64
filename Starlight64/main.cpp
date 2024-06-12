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
    Engine gameEngine;
    int result = gameEngine.InitalizeEngine();
    if (result != 1)
        return result;
    gameEngine.StartEngine();
    gameEngine.Shutdown();
    return 1;
}