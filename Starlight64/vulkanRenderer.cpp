#include "vulkanRenderer.h"

/*
    Renderer::initalizeRenderer() - Returns int [error code. 1 = ran sucessfully]

*/
int Renderer::initalizeRenderer(SLE64_BuildData* gameData)
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
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    m_window = glfwCreateWindow(gameData->windowData->windowHeight, gameData->windowData->windowWidth, 
        gameData->gameName, NULL, NULL);
    if (!m_window)
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
    m_appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    m_appInfo.pApplicationName = "Collectathon 64";
    m_appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
    m_appInfo.pEngineName = "Starlight 64";
    m_appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
    m_appInfo.apiVersion = VK_API_VERSION_1_0;
    //Initalize instanceInfo
    m_instanceInfo.enabledExtensionCount = count;
    m_instanceInfo.ppEnabledExtensionNames = extensions;
    m_instanceInfo.pApplicationInfo = &m_appInfo;

    if (pfnCreateInstance(&m_instanceInfo, 0, &m_instance) != VK_SUCCESS)
    {
        std::cout << "Error: Could not create Vulkan Instance" << std::endl;
        return -2;
    }

    
    if (glfwCreateWindowSurface(m_instance, m_window, NULL, &m_surface) != VK_SUCCESS)
    {
        std::cout << "Error: Could not create window surface!" << std::endl;
        return -3;
    }
#pragma endregion

    return 1;
}
void Renderer::graphicsUpdate()
{
    while (!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();
    }
}

void Renderer::error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void Renderer::Shutdown()
{
    //Destroy window
    glfwDestroyWindow(m_window);
    //Destroy Surface
    PFN_vkDestroySurfaceKHR pftDestroySurface = (PFN_vkDestroySurfaceKHR)
        glfwGetInstanceProcAddress(NULL, "vkDestroySurfaceKHR");

    pftDestroySurface(m_instance,m_surface,0);
}
