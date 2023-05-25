#include "renderer.h"

int Renderer::startup()
{
    log_ptr = MLogger::get();
    startup_glfw();
    startup_vulkan();
    startup_surface();
    startup_physical_devices();
    startup_logical_devices();
    return 0;
}

int Renderer::shutdown()
{
    glfwDestroyWindow(window);
    window = nullptr;
    vkDestroySurfaceKHR(instance, surface, nullptr);
    vkDestroyInstance(instance, nullptr);
    vkDestroyDevice(logical_device, nullptr);
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
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(500, 500, "Vulkan", nullptr, nullptr);
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
    create_instance_or_fail(vkCreateInstance(&createInfo, nullptr, &instance));
}

void Renderer::startup_surface()
{
    if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
        auto err = std::runtime_error("failed to create window surface!");
        log_ptr->log_error(err);
        throw err;
    }
}

void Renderer::startup_physical_devices()
{
    uint32_t device_count = 0;
    vkEnumeratePhysicalDevices(instance, &device_count, nullptr);

    if (device_count == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(device_count);
    vkEnumeratePhysicalDevices(instance, &device_count, devices.data());

    for (const auto& device : devices) {
        if (is_device_usable(device)) {
            log_ptr->log_message("Physical device linked", "[VULKAN]");
            physical_device = device;
            break;
        }
    }

    if (physical_device == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}

void Renderer::startup_logical_devices()
{
    QueueFamilyIndices indices = find_queue_families(physical_device);
    std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
    std::vector<uint32_t> unique_queue_families = {*indices.graphics_family, *indices.present_family};

    float queue_priority = 1.0f;
    for (uint32_t queueFamily : unique_queue_families) {
        VkDeviceQueueCreateInfo queue_create_info{};
        queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queue_create_info.queueFamilyIndex = queueFamily;
        queue_create_info.queueCount = 1;
        queue_create_info.pQueuePriorities = &queue_priority;
        queue_create_infos.push_back(queue_create_info);
    }
    VkDeviceQueueCreateInfo queue_create_info{};
    queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_create_info.queueFamilyIndex = *indices.graphics_family;
    queue_create_info.queueCount = 1;
    queue_create_info.pQueuePriorities = &queue_priority;
    VkPhysicalDeviceFeatures device_features{};
    VkDeviceCreateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    create_info.pQueueCreateInfos = queue_create_infos.data();
    create_info.pEnabledFeatures = &device_features;
    create_info.enabledExtensionCount = 0;
    create_info.queueCreateInfoCount = static_cast<uint32_t>(queue_create_infos.size());
    std::vector<char*> validation_layers;
    // @TODO validation layers
    if (false) {
        create_info.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
        create_info.ppEnabledLayerNames = validation_layers.data();
    } else {
        create_info.enabledLayerCount = 0;
    }

    if (vkCreateDevice(physical_device, &create_info, nullptr, &logical_device) != VK_SUCCESS) {
        std::runtime_error err = std::runtime_error("failed to create logical device!");
        log_ptr->log_error(err);
        throw err;
    }
    vkGetDeviceQueue(logical_device, *indices.present_family, 0, &present_queue);
    vkGetDeviceQueue(logical_device, *indices.graphics_family, 0, &graphics_queue);
}

bool Renderer::is_device_usable(VkPhysicalDevice device)
{
        QueueFamilyIndices indices = find_queue_families(device);
        return indices.is_complete();
}

QueueFamilyIndices Renderer::find_queue_families(VkPhysicalDevice device)
{
        QueueFamilyIndices indices;

        uint32_t queue_family_count = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, nullptr);

        std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_families.data());
        uint32_t i = 0;
        for (const auto& queue_family : queue_families) {
            if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphics_family = &i;
            }
            VkBool32 present_support = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &present_support);
            if (present_support) {
                indices.present_family = &i;
            }
            if (indices.is_complete()) {
                break;
            }

            i++;
        }

        return indices;
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
