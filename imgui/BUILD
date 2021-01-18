load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "imgui_lib",
    srcs = [
        "GL/gl3w.c",
        "GL/gl3w.h",
        "GL/glcorearb.h",
        "imconfig.h",
        "imgui.cpp",
        "imgui.h",
        "imgui_demo.cpp",
        "imgui_draw.cpp",
        "imgui_impl_opengl3.cpp",
        "imgui_impl_opengl3.h",
        "imgui_impl_sdl.cpp",
        "imgui_impl_sdl.h",
        "imgui_internal.h",
        "imgui_sdl.cpp",
        "imgui_sdl.h",
        "imgui_widgets.cpp",
        "imstb_rectpack.h",
        "imstb_textedit.h",
        "imstb_truetype.h",
    ],
    hdrs = [
        "imgui.cpp",
        "imgui_demo.cpp",
        "imgui_draw.cpp",
        "imgui_sdl.cpp",
        "imgui_widgets.cpp",
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
    visibility = [
        "//main:__pkg__", 
        "//src:__pkg__",
        ],
)

cc_binary(
    name = "imgui_demo",
    srcs = [
        "main.cpp",
    ],
    copts = [
        "-std=c++14",
        "-Wformat",
    ],
    defines = [
        "IMGUI_IMPL_OPENGL_LOADER_GL3W",
        "REENTRANT",
    ],
    linkopts = ["-lSDL2 -lGL -ldl -lSDL2_mixer"],
    deps = [
        ":func_lib",
        ":imgui_lib",
    ],
)
