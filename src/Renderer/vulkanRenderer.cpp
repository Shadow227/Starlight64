#include "vulkanRenderer.h"

bool renderer::initalizeVulkan(VKContext* context)
{
     const char* extensions[2] =
     {
     VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
     VK_KHR_SURFACE_EXTENSION_NAME
     };
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Collectathon 64";
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
    appInfo.pEngineName = "Starlight 64";
    appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
    appInfo.apiVersion = VK_API_VERSION_1_0;
    VkInstanceCreateInfo instanceInfo = {};
    instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo.pApplicationInfo = &appInfo;
    instanceInfo.ppEnabledExtensionNames = extensions;
    instanceInfo.enabledExtensionCount = 2;

    VkResult result = vkCreateInstance(&instanceInfo, NULL, &context->instance);
    if (result != VK_SUCCESS) {
        return false;
    }


   win32SurfaceInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
   win32SurfaceInfo.hwnd = window;
   win32SurfaceInfo.hinstance = GetModuleHandleA(0);

   if(vkCreateWin32SurfaceKHR(context->instance,&win32SurfaceInfo,0,&context->surface) != VK_SUCCESS)
   {
        return false;
   }

   

    return true;
}

bool renderer::createWindowR()
{
    if(!createWindow(&window))
    {
        return false;
    }
    return true;
}

void renderer::graphicsUpdate()
{
    while(getRunning())
    {
        plateform_update_window(window);
    }
}
