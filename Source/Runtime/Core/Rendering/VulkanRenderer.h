#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <vulkan/vulkan.h>
#include <vector>

namespace polaris {
    class VulkanRenderer {
    public:
        VulkanRenderer(SDL_Window* window);
        ~VulkanRenderer();

        void render();

    private:
        void initVulkan();
        void cleanup();

        SDL_Window* m_pWindow;
        VkInstance m_instance;
        VkSurfaceKHR m_surface;
        VkPhysicalDevice m_physicalDevice;
        VkDevice m_device;
        VkQueue m_graphicsQueue;
        VkCommandPool m_commandPool;
        VkSwapchainKHR m_swapchain;
        std::vector<VkImage> m_swapchainImages;
        std::vector<VkImageView> m_swapchainImageViews;
        VkRenderPass m_renderPass;
        std::vector<VkFramebuffer> m_swapchainFramebuffers;
        VkCommandBuffer m_commandBuffer;
        VkSemaphore m_imageAvailableSemaphore;
        VkSemaphore m_renderFinishedSemaphore;
        VkExtent2D m_extent;
    };
}