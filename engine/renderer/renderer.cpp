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
    appInfo.pEngineName = "NYX Engine";
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
    create_instance_or_fail(vkCreateInstance(&createInfo, nullptr, vulkan_ptr));
    log_ptr->log_message("Vulkan initialized");

}

void Renderer::create_instance_or_fail(VkResult result)
{
    if (result == VK_SUCCESS)
    {
        log_ptr->log_message("Vulkan instance created");
        return;
    }

    std::runtime_error err = std::runtime_error("Unknown error");
    switch (result) {
        case VK_NOT_READY:
            err = std::runtime_error("VK_NOT_READY: A fence or query has not yet completed.");
            break;
        case VK_TIMEOUT:
            err = std::runtime_error("VK_TIMEOUT: A wait operation has not completed in the specified time.");
            break;
        case VK_EVENT_SET:
            err = std::runtime_error("VK_EVENT_SET: An event is signaled.");
            break;
        case VK_EVENT_RESET:
            err = std::runtime_error("VK_EVENT_RESET: An event is unsignaled.");
            break;
        case VK_INCOMPLETE:
            err = std::runtime_error("VK_INCOMPLETE: A return array was too small for the result.");
            break;
        case VK_ERROR_OUT_OF_HOST_MEMORY:
            err = std::runtime_error("VK_ERROR_OUT_OF_HOST_MEMORY: A host memory allocation has failed.");
            break;
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            err = std::runtime_error("VK_ERROR_OUT_OF_DEVICE_MEMORY: A device memory allocation has failed.");
            break;
        case VK_ERROR_INITIALIZATION_FAILED:
            err = std::runtime_error("VK_ERROR_INITIALIZATION_FAILED: Initialization of an object has failed.");
            break;
        case VK_ERROR_DEVICE_LOST:
            err = std::runtime_error("VK_ERROR_DEVICE_LOST: The logical or physical device has been lost.");
            break;
        case VK_ERROR_MEMORY_MAP_FAILED:
            err = std::runtime_error("VK_ERROR_MEMORY_MAP_FAILED: Mapping of a memory object has failed.");
            break;
        case VK_ERROR_LAYER_NOT_PRESENT:
            err = std::runtime_error("VK_ERROR_LAYER_NOT_PRESENT: A requested layer is not present or could not be loaded.");
            break;
        case VK_ERROR_EXTENSION_NOT_PRESENT:
            err = std::runtime_error("VK_ERROR_EXTENSION_NOT_PRESENT: A requested extension is not supported.");
            break;
        case VK_ERROR_FEATURE_NOT_PRESENT:
            err = std::runtime_error("VK_ERROR_FEATURE_NOT_PRESENT: A requested feature is not supported.");
            break;
        case VK_ERROR_INCOMPATIBLE_DRIVER:
            err = std::runtime_error("VK_ERROR_INCOMPATIBLE_DRIVER: The requested version of the driver is not supported.");
            break;
        case VK_ERROR_TOO_MANY_OBJECTS:
            err = std::runtime_error("VK_ERROR_TOO_MANY_OBJECTS: Too many objects of the type have already been created.");
            break;
        case VK_ERROR_FORMAT_NOT_SUPPORTED:
            err = std::runtime_error("VK_ERROR_FORMAT_NOT_SUPPORTED: A requested format is not supported.");
            break;
        case VK_ERROR_FRAGMENTED_POOL:
            err = std::runtime_error("VK_ERROR_FRAGMENTED_POOL: A pool allocation has failed due to fragmentation.");
            break;
        case VK_ERROR_UNKNOWN:
            err = std::runtime_error("VK_ERROR_UNKNOWN: An unknown error has occurred.");
            break;
        case VK_ERROR_OUT_OF_POOL_MEMORY:
            err = std::runtime_error("VK_ERROR_OUT_OF_POOL_MEMORY: A pool memory allocation has failed.");
            break;
        case VK_ERROR_INVALID_EXTERNAL_HANDLE:
            err = std::runtime_error("VK_ERROR_INVALID_EXTERNAL_HANDLE: An external handle is not a valid handle.");
            break;
        case VK_ERROR_FRAGMENTATION:
            err = std::runtime_error("VK_ERROR_FRAGMENTATION: A descriptor pool creation has failed due to fragmentation.");
            break;
        case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
            err = std::runtime_error("VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS: An invalid capture address is accessed.");
            break;
        case VK_PIPELINE_COMPILE_REQUIRED:
            err = std::runtime_error("VK_PIPELINE_COMPILE_REQUIRED: A pipeline compilation is required.");
            break;
        case VK_ERROR_SURFACE_LOST_KHR:
            err = std::runtime_error("VK_ERROR_SURFACE_LOST_KHR: The surface is no longer available.");
            break;
        case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
            err = std::runtime_error("VK_ERROR_NATIVE_WINDOW_IN_USE_KHR: Native window in use.");
            break;
        case VK_SUBOPTIMAL_KHR:
            err = std::runtime_error("VK_SUBOPTIMAL_KHR: Suboptimal KHR");
            break;
        case VK_ERROR_OUT_OF_DATE_KHR:
            err = std::runtime_error("VK_SUBOPTIMAL_KHR: Out of date KHR");
            break;
        case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
            err = std::runtime_error("VK_ERROR_INCOMPATIBLE_DISPLAY_KHR: ");
            break;
        case VK_ERROR_VALIDATION_FAILED_EXT:
            err = std::runtime_error("VK_ERROR_VALIDATION_FAILED_EXT: ");
            break;
        case VK_ERROR_INVALID_SHADER_NV:
            err = std::runtime_error("VK_ERROR_INVALID_SHADER_NV: ");
            break;
    }
    log_ptr->log_error(err);
    throw err;
}
