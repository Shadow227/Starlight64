#define GLFW_INCLUDE_VULKAN 
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/Include/GLFW/glfw3.h>
#include <GLFW/Include/GLFW/glfw3native.h>
#include<iostream>
#include <optional>
#include <set>
#include "gameCore.h"


/*
    The vulkan inplementation here is being learned from https://vulkan-tutorial.com/
    some code has taken inspiration from here as I learn vulkan OR someone else refactors it
    to be better.

    Some other features I am doing my own personal way of this, so we will see how it works in the end.
*/
struct QueueFamilyIndices {
    std::optional<uint32_t> m_graphicsFamily;
    std::optional<uint32_t> m_presentFamily;

    inline bool isValid() { return m_graphicsFamily.has_value() && m_presentFamily.has_value(); }
};

    class Renderer
    {
        //Member Vars
    private:
        //GLFW
        GLFWwindow* m_window;
        //Vulkan
        VkApplicationInfo m_appInfo = {};
        VkInstanceCreateInfo m_instanceInfo = {};
        VkInstance m_instance;
        VkSurfaceKHR m_surface;
        //Queues
        VkQueue m_graphicsQueue;
        VkQueue m_presentQueue;
        //Vulkan Devices
        VkPhysicalDevice m_graphicsDevice = VK_NULL_HANDLE;
        VkDevice m_logicalDevice;
        //Functions
    public:
        int initalizeRenderer(SLE64_BuildData* gameData);
        void graphicsUpdate();
        void error_callback(int error, const char* description);
        void Shutdown();

    private:
        bool checkDevice(VkPhysicalDevice device);
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    };