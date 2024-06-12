
#include "vulkanRenderer.h"
/*
     Starlight 64, Project started 6/11/2024.
     Code written by: George Skaggs
*/

//Application Entry point
//TODO: Seperate "game" and "engine"
int main()
{
    //TODO: Initalize Engine
    //Initalize the graphicsEngine
    Renderer graphicsEngine;
    int result = graphicsEngine.initalizeRenderer();
    //Check result and return error code if result was not a 1.
    if (result != 1) 
        return result;

    //TODO: update Loop
    graphicsEngine.graphicsUpdate();

    return 1;
}