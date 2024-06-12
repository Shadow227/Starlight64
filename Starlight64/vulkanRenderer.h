#define GLFW_INCLUDE_VULKAN 
#include <GLFW/glfw3.h>
#include<iostream>
/*
     Main renderer class. I was following a tutorial to start learning vulkan, however something annoyed me
     when it came to the person NOT making this a cpp and h file. so I took a more object oriented approch
     and so far its doing me good!

     This class will handle all of the graphics. From 3D models to 2D text!
*/


class Renderer
{
    //Member Vars
private:
    GLFWwindow* window;
    VkApplicationInfo appInfo = {};
    VkInstance instance;

    //Functions
public:
    int initalizeRenderer();
    void graphicsUpdate();

};