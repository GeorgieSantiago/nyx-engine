#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <iostream>
#include "../common/module.h"
#include "../common/logger.h"
#include "default_pipeline.h"
#include <vector>
#include <string>

struct QueueFamilyIndices {
    uint32_t *graphics_family = nullptr;
    uint32_t *present_family = nullptr;
    bool is_complete() {
        return graphics_family != nullptr && present_family != nullptr;
    }
};

// Execute basic window
class Renderer : public Module
{
private:
    DefaultPipeline graphics_pipeline{
        "shaders/build/simple_shader.vert.spv",
        "shaders/build/simple_shader.frag.spv"
    };
    MLogger* log_ptr;
    GLFWwindow* window;
    VkInstance instance;
    VkPhysicalDevice physical_device;
    VkDevice logical_device;
    VkQueue graphics_queue;
    VkQueue present_queue;
    VkSurfaceKHR surface;
    void startup_glfw();
    void startup_vulkan();
    void startup_surface();
    void startup_physical_devices();
    void startup_logical_devices();
    void create_instance_or_fail(VkResult result);
    bool is_device_usable(VkPhysicalDevice device);
    QueueFamilyIndices find_queue_families(VkPhysicalDevice device);
public:
    int startup() override;
    int shutdown() override;
    int update();
};