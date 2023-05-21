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
// Execute basic window
class Renderer : public Module
{
private:
    DefaultPipeline graphics_pipeline{
        "shaders/build/simple_shader.vert.spv",
        "shaders/build/simple_shader.frag.spv"
    };
    MLogger* log_ptr;
    GLFWwindow* window_ptr;
    VkInstance* vulkan_ptr;
    void startup_glfw();
    void startup_vulkan();
    void create_instance_or_fail(VkResult result);
public:
    int startup() override;
    int shutdown() override;
    int update();
};