#define GLFW_INCLUDE_VULKAN 
#include <GLFW/Include/GLFW/glfw3.h>
#include<iostream>
#include "gameCore.h"
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
        GLFWwindow* m_window;
        VkApplicationInfo m_appInfo = {};
        VkInstanceCreateInfo m_instanceInfo = {};
        VkInstance m_instance;
        VkSurfaceKHR m_surface;

        //Functions
    public:
        int initalizeRenderer(SLE64_BuildData* gameData);
        void graphicsUpdate();
        void error_callback(int error, const char* description);
        void Shutdown();

    };