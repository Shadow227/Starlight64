#include "vulkanRenderer.h"
//This function initalizes the Vulkan device in order to start getting vulkan to work!
//TODO: Change this to work with GLFW
//NOTE: Unknown bug! - Sometimes the vkCreateInstance() will have a nullptr error. I fixed this
//Using chatGPT to debug and really all it said was that some of the infos
//just needed more info. Weird thing was it worked before hand and randomly broke while working.
//Need to look more into this later.
bool renderer::initalizeVulkan(VKContext* context)
{
    //Simple storage for different extensions being used
     const char* extensions[2] =
     {
     VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
     VK_KHR_SURFACE_EXTENSION_NAME
     };
     //Intalize appInfo and instanceInfo
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Collectathon 64";
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
    appInfo.pEngineName = "Starlight 64";
    appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
    appInfo.apiVersion = VK_API_VERSION_1_0;
    //NOTE: This is also in the .h, but if I remove either of them I get a nullptr error (see above)
    VkInstanceCreateInfo instanceInfo = {};
    instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo.pApplicationInfo = &appInfo;
    instanceInfo.ppEnabledExtensionNames = extensions;
    instanceInfo.enabledExtensionCount = 2;
    //Attempt to create the vulkan instance. If we fail, return false so main can give us an error code.
    VkResult result = vkCreateInstance(&instanceInfo, NULL, &context->instance);
    if (result != VK_SUCCESS) {
        return false;
    }

    //Started this for Renderering on the screen, got a little too lost so thats why im switching to
    //using GLFW
   win32SurfaceInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
   win32SurfaceInfo.hwnd = window;
   win32SurfaceInfo.hinstance = GetModuleHandleA(0);

   if(vkCreateWin32SurfaceKHR(context->instance,&win32SurfaceInfo,0,&context->surface) != VK_SUCCESS)
   {
        return false;
   }

   

    return true;
}
/*
    This function create the win64/32 window. I might make this a dedicated different function later
    after the update to GLFW.
    TODO: Update this to work with GLFW!
*/
bool renderer::createWindowR()
{
    if(!createWindow(&window))
    {
        return false;
    }
    return true;
}
//Just a simple update loop.
//TODO: Graphics updates need to happen here. Not just msg checking.
void renderer::graphicsUpdate()
{
    while(getRunning())
    {
        plateform_update_window(window);
    }
}
