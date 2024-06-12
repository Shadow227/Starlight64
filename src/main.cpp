#include<iostream>
#include "Renderer/vulkanRenderer.cpp"
/*
     Starlight 64, Project started 6/11/2024.
     Code written by: George Skaggs
*/

//Application Entry point
//TODO: Seperate "game" and "engine"
int main()
{
     //Create a renderer object and attempt to create a window using the windows platefore
     //TODO: Update this using GLFW
     renderer rend;
     if(!rend.createWindowR())
          return -1;
     //Creeate our Vulkan context and attempt to intalize vulkan
     //TODO:Update this using GLFW
     VKContext* context = new VKContext();
     if(!rend.initalizeVulkan(context))
          return -2;
     //Start Graphics update cycle.
     rend.graphicsUpdate();

     //TODO: Add cleanup!

     return 1;
}