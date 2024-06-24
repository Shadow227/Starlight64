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
        //Create vulkan instance
        if (pfnCreateInstance(&m_instanceInfo, 0, &m_instance) != VK_SUCCESS)
        {
            std::cout << "Error: Could not create Vulkan Instance" << std::endl;
            return -2;
        }

        //create window surface
        if (glfwCreateWindowSurface(m_instance, m_window, NULL, &m_surface) != VK_SUCCESS)
        {
            std::cout << "Error: Could not create window surface!" << std::endl;
            return -3;
        }

        PFN_vkEnumeratePhysicalDevices pfnEnumeratePhysical = (PFN_vkEnumeratePhysicalDevices)
            glfwGetInstanceProcAddress(NULL, "vkEnumeratePhysicalDevices");

        //check how many graphics devices that can support vulkan exist
        uint32_t deviceCount = 0;
        pfnEnumeratePhysical(m_instance, &deviceCount, nullptr);
        if (deviceCount == 0) 
        {
            std::cout << "ERROR: No graphics cards that support vulkan found!";
            return -6;
        }
        //Save all devices found
        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data());

        //Loop through and find the first device that meets our requirements for this renderer
        for (const auto& device : devices) 
            if (checkDevice(device)) 
            {
                m_graphicsDevice = device;
                break;
            }
        //another error check for graphics devices, never can be too safe!
        if (m_graphicsDevice == VK_NULL_HANDLE) 
        {
            std::cout << "ERROR: Graphics device not set!";
            return -6;
        }

        QueueFamilyIndices indices = findQueueFamilies(m_graphicsDevice);

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = { indices.m_graphicsFamily.value(), indices.m_presentFamily.value() };

        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{};

        VkDeviceCreateInfo logiccreateInfo{};
        logiccreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        logiccreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        logiccreateInfo.pQueueCreateInfos = queueCreateInfos.data();
        logiccreateInfo.pEnabledFeatures = &deviceFeatures;
        logiccreateInfo.enabledExtensionCount = 0;
        logiccreateInfo.enabledLayerCount = 0;
        

        if (vkCreateDevice(m_graphicsDevice, &logiccreateInfo, nullptr, &m_logicalDevice) != VK_SUCCESS) {
            return -80;
        }

        vkGetDeviceQueue(m_logicalDevice, indices.m_graphicsFamily.value(), 0, &m_graphicsQueue);
        vkGetDeviceQueue(m_logicalDevice, indices.m_presentFamily.value(), 0, &m_presentQueue);
        //Make our device create info
        VkDeviceCreateInfo logical_createInfo{};
        logical_createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        logical_createInfo.pQueueCreateInfos = queueCreateInfos.data();
        logical_createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());;
        logical_createInfo.pEnabledFeatures = &deviceFeatures;

        vkGetDeviceQueue(m_logicalDevice, indices.m_presentFamily.value(), 0, &m_presentQueue);
        //Default, edit later.
        logical_createInfo.enabledExtensionCount = 0;
        //safety net for older versions of vulkan
        logical_createInfo.enabledLayerCount = 0;

        PFN_vkCreateDevice pfnCreateDevice = (PFN_vkCreateDevice)
            glfwGetInstanceProcAddress(NULL, "vkCreateDevice");
        if (pfnCreateDevice(m_graphicsDevice, &logical_createInfo, nullptr, &m_logicalDevice) != VK_SUCCESS) 
        {
            std::cout << "Error: Could not create logical device!";
            return -7;
        }

        vkGetDeviceQueue(m_logicalDevice, indices.m_graphicsFamily.value(), 0, &m_graphicsQueue);

        //win32 surface creation
        VkWin32SurfaceCreateInfoKHR win_createInfo{};
        win_createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        win_createInfo.hwnd = glfwGetWin32Window(m_window);
        win_createInfo.hinstance = GetModuleHandle(nullptr);

        if (vkCreateWin32SurfaceKHR(m_instance, &win_createInfo, nullptr, &m_surface) != VK_SUCCESS) 
        {
            std::cout << "Error: Could not create win32 surface!";
            return -80;
        }
        //Window surface linkage, NOT PLATFORM SPECIFIC
        if (glfwCreateWindowSurface(m_instance, m_window, nullptr, &m_surface) != VK_SUCCESS) 
        {
            std::cout << "Error: Could not create window surface!";
            return -81;
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
        //destroy logical device
        vkDestroyDevice(m_logicalDevice, nullptr);
        //Destroy Surface
        PFN_vkDestroySurfaceKHR pftDestroySurface = (PFN_vkDestroySurfaceKHR)
            glfwGetInstanceProcAddress(NULL, "vkDestroySurfaceKHR");
        pftDestroySurface(m_instance, m_surface, 0);
        //Destroy window
        glfwDestroyWindow(m_window);
        //Terminate GLFW
        glfwTerminate();
    }
    /*
        checkDevice, returns if there is a graphics card that supports what we need.
    */
    bool Renderer::checkDevice(VkPhysicalDevice device)
    {
        QueueFamilyIndices indices = findQueueFamilies(device);

        return indices.isValid();
    }
    /*
        Finds the different QueueFamiles to see what our graphics device can do.
    */
    QueueFamilyIndices Renderer::findQueueFamilies(VkPhysicalDevice device)
    {
        QueueFamilyIndices indices;
        //find our family count on the graphics device.
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
        //Start getting our familyProperites and save them to a vector.
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
        //Loop through the queuefamily vector to find if our devices have everything we need.
        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
                indices.m_graphicsFamily = i;
            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_surface, &presentSupport);
            if (presentSupport) {
                indices.m_presentFamily = i;
            }
            if (indices.isValid()) 
              break; 
            i++;
        }
        return indices;
    }
