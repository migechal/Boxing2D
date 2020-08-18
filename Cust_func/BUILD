load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "func_lib",
    srcs = [
        "myfuncs.cpp",
    ],
    hdrs = [
        "header.h",
    ],
    copts = [
        "-std=c++14",
        "-Wformat",
    ],
    defines = [
        "IMGUI_IMPL_OPENGL_LOADER_GL3W",
        "REENTRANT",
    ],
    includes = ["."],
    visibility = ["//main:__pkg__"],
)
