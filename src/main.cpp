#include<iostream>

#include "Renderer/vulkanRenderer.cpp"

int main()
{
    renderer rend;

   if(!rend.createWindowR())
   {
        return -1;
   }
   VKContext* context = new VKContext();
   //context.instance = VK_NULL_HANDLE;
   if(!rend.initalizeVulkan(context))
   {
        return -2;
   }
   rend.graphicsUpdate();
    
    return 1;
}