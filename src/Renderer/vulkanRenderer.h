#include "Plateforms/win32.cpp"
#include<vulkan/vulkan.h>
#include<vulkan/vulkan_win32.h>



struct VKContext
{
    VkInstance instance = VK_NULL_HANDLE;
    VkSurfaceKHR surface;
};

class renderer
{

     VkWin32SurfaceCreateInfoKHR win32SurfaceInfo;
     VkApplicationInfo appInfo;
     HWND window = 0;



public:
     bool initalizeVulkan(VKContext* context);
     bool createWindowR();
     void graphicsUpdate();

};