#include "renderer.h"

int Renderer::startup()
{
    log_ptr = MLogger::get();
    startup_glfw();
    startup_vulkan();
    return 0;
}

int Renderer::shutdown()
{
    glfwDestroyWindow(window_ptr);
    window_ptr = nullptr;
    vkDestroyInstance(*vulkan_ptr, nullptr);
    glfwTerminate();
    log_ptr->log_message("Vulkan shutdown");
    return 0;
}

int Renderer::update()
{
    glfwPollEvents();
    return 0;
}

void Renderer::startup_glfw()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window_ptr = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    glm::mat4 matrix;
    glm::vec4 vec;
    glm::vec4 test = matrix * vec;
    log_ptr->log_message(extensionCount + " extensions supported\n");
    log_ptr->log_message("GLFW started");
}

void Renderer::startup_vulkan()
{
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;
    if (vkCreateInstance(&createInfo, nullptr, vulkan_ptr) != VK_SUCCESS) {
        std::runtime_error err = std::runtime_error("failed to create instance!");
        log_ptr->log_error(err);
        throw err;
    }
    log_ptr->log_message("Vulkan initialized");

}