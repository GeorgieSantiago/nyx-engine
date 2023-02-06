# env_setup/BUILD
load("@rules_cc//cc:defs.bzl", "cc_binary")

# engine
cc_library(
    name = "nyx_engine",
    srcs = ["engine/example/example.cpp", "engine/vulkan_init.cpp"],
    hdrs = ["engine/example/example.h", "engine/vulkan_init.h"],
    copts = ["/DCOMPILING_NYX_ENGINE_DLL"],
    deps = [
        "//third-party/glfw",
        "//third-party/glm",
        "@rules_vulkan//vulkan:vulkan_cc_library"
    ],
)

cc_test(
    name = "nyx_engine_test",
    size = "small",
    srcs = ["engine/example/example.test.cpp"],
    deps = ["@com_google_googletest//:gtest_main"],
)

# Console
cc_binary(
    name = "nyx_console",
    srcs = ["console/main.cc"],
    deps = [":nyx_engine"],
)