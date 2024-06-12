#include "vulkanRenderer.h"

/*
    Renderer::initalizeRenderer() - Returns int [error code. 1 = ran sucessfully]

*/
int Renderer::initalizeRenderer()
{
    //Initalize GLFW otherwise we need to close
    if (!glfwInit())
    {
        std::cout << "ERROR: GLFW UNABLE TO INITALIZE!" << std::endl;
        return -12;
    }
    //Next, check if vulkan is supported. If its not, Well thats an issue!
    if (!glfwVulkanSupported())
    {
        std::cout << "ERROR: Vulkan API not supported! Please make sure vulkan is setup correctly!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(1280, 720, "Starlight 64 Game Engine", NULL, NULL);
    if(!window)
    {
        std::cout << "ERROR: WIndow creation failed" << std::endl;
        return -5;
    }

    //Intalize appInfo and instanceInfo
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Collectathon 64";
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
    appInfo.pEngineName = "Starlight 64";
    appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    uint32_t count;
    const char** extensions = glfwGetRequiredInstanceExtensions(&count);
    VkInstanceCreateInfo instanceInfo = {};

    memset(&instanceInfo, 0, sizeof(instanceInfo));
    instanceInfo.enabledExtensionCount = count;
    instanceInfo.ppEnabledExtensionNames = extensions;
    instanceInfo.pApplicationInfo = &appInfo;
    
    if (vkCreateInstance(&instanceInfo,0,&instance) != VK_SUCCESS) 
    {
        std::cout << "ERROR CREATING VULKAN INSTANCE!" << std::endl;
        return -2;
    }

    VkSurfaceKHR surface;
    VkResult err = glfwCreateWindowSurface(instance, window, NULL, &surface);
    if (err)
    {
        std::cout << "Error: Could not create window surface!" << std::endl;
        return -3;
    }

    return 1;
}
void Renderer::graphicsUpdate()
{
    while (!glfwWindowShouldClose(window))
    {
        // Keep running
    }
}
/*
    This function create the win64/32 window. I might make this a dedicated different function later
    after the update to GLFW.
    TODO: Update this to work with GLFW!
*/

//Just a simple update loop.
//TODO: Graphics updates need to happen here. Not just msg checking.
