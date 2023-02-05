cc_library(
    name = "nyx_engine",
    srcs = ["Engine/hello.cpp"],
    hdrs = ["Engine/hello.h"],
    copts = ["/DCOMPILING_NYX_ENGINE_DLL"],
)

cc_binary(
    name = "nyx_console",
    srcs = ["Console/main.cc"],
    deps = [":nyx_engine"],
)