#include "vulkanRenderer.h"

/*
    Renderer::initalizeRenderer() - Returns int [error code. 1 = ran sucessfully]

*/
int Renderer::initalizeRenderer()
{
#pragma region GLFW Init
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
    if (!window)
    {
        std::cout << "ERROR: WIndow creation failed" << std::endl;
        return -5;
    }
#pragma endregion

#pragma region VulkanSetup
    //So, WE need to do this in order to quarry the correct vkCreateInstance function.
    //This variable is a function pointer fundamentally even if it doesnt
    //seem like it. Very interesting!
    //Learned form https://www.glfw.org/docs/3.3/vulkan_guide.html#vulkan_window
    PFN_vkCreateInstance pfnCreateInstance = (PFN_vkCreateInstance)
        glfwGetInstanceProcAddress(NULL, "vkCreateInstance");

    //Get extensions needed by GLFW for vulkan.
    uint32_t count;
    const char** extensions = glfwGetRequiredInstanceExtensions(&count);

    //Intalize appInfo
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Collectathon 64";
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
    appInfo.pEngineName = "Starlight 64";
    appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
    appInfo.apiVersion = VK_API_VERSION_1_0;
    //Initalize instanceInfo
    instanceInfo.enabledExtensionCount = count;
    instanceInfo.ppEnabledExtensionNames = extensions;
    instanceInfo.pApplicationInfo = &appInfo;

    if (pfnCreateInstance(&instanceInfo, 0, &instance) != VK_SUCCESS)
    {
        std::cout << "Error: Could not create Vulkan Instance" << std::endl;
        return -2;
    }

    
    if (glfwCreateWindowSurface(instance, window, NULL, &surface) != VK_SUCCESS)
    {
        std::cout << "Error: Could not create window surface!" << std::endl;
        return -3;
    }
#pragma endregion

    return 1;
}
void Renderer::graphicsUpdate()
{
    while (!glfwWindowShouldClose(window))
    {
        // Keep running
    }
}
