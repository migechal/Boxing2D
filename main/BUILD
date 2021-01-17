load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "game",
    srcs = [
        "main.cpp",
    ],
    copts = [
        "-std=c++17",
        "-Wall",
        "-Wformat",
    ],
    defines = [
        "IMGUI_IMPL_OPENGL_LOADER_GL3W",
        "REENTRANT",
    ],
    linkopts = ["-lSDL2 -lGL -ldl -lSDL2_mixer -lSDL2_ttf"],
    deps = [
        "//imgui:imgui_lib",
        "//src:Sources",
    ],
)
