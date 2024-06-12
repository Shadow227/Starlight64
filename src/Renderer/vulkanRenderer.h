#include "Plateforms/win32.cpp"
#include<vulkan/vulkan.h>
#include<vulkan/vulkan_win32.h>
/*
     Main renderer class. I was following a tutorial to start learning vulkan, however something annoyed me
     when it came to the person NOT making this a cpp and h file. so I took a more object oriented approch
     and so far its doing me good!

     This class will handle all of the graphics. From 3D models to 2D text!
*/

//TODO: Change this to work with GLFW
struct VKContext
{
    VkInstance instance = VK_NULL_HANDLE;
    VkSurfaceKHR surface;
};

class renderer
{
     //Member Vars
private:
     VkWin32SurfaceCreateInfoKHR win32SurfaceInfo;
     VkApplicationInfo appInfo;
     HWND window = 0;
     //Functions
public:
     bool initalizeVulkan(VKContext* context);
     bool createWindowR();
     void graphicsUpdate();

};