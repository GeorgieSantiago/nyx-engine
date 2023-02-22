# env_setup/BUILD
load("@rules_cc//cc:defs.bzl", "cc_binary")
test_glob = glob(["engine/**/*.test.*"])

cc_library(
    name = "mathfu", 
    includes = ["third-party/mathfu/include/"],
    deps = ["mathfu-internal"],
    visibility = ["//visibility:public"],
)

cc_import(
    name = "mathfu-internal",
    hdrs = glob(["third-party/mathfu/**/*.h"]),
    visibility = ["//visibility:private"],
)

# engine
cc_library(
    name = "nyx_engine",
    srcs = glob(["engine/**/*.cpp"], test_glob),
    hdrs = glob(["engine/**/*.h"], test_glob),
    copts = ["/DCOMPILING_NYX_ENGINE_DLL"],
    deps = [
        ":mathfu",
        "//third-party/glfw",
        "//third-party/glm",
        "@rules_vulkan//vulkan:vulkan_cc_library",
        "@com_github_google_glog//:glog",
        "@com_google_absl//absl/strings",
    ],
)

cc_test(
    name = "nyx_engine_test",
    size = "small",
    srcs = ["engine/example/example.test.cpp"],
    deps = ["@com_google_googletest//:gtest_main"],
)

# console
cc_binary(
    name = "nyx_console",
    srcs = ["console/main.cc"],
    deps = [":nyx_engine"],
)