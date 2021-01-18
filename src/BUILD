load("@rules_cc//cc:defs.bzl", "cc_library")
cc_library(
    name = "Sources",
    srcs = glob(["*.cpp"]),
    defines = [
        "IMGUI_IMPL_OPENGL_LOADER_GL3W",
        "REENTRANT",
    ],
    deps = [
        "//headers:HeaderFiles",
        "//imgui:imgui_lib",
    ],
    visibility = ["//main:__pkg__"],
)