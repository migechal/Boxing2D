load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "imgui_demo",
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
        "imgui_widgets.cpp",
        "imstb_rectpack.h",
        "imstb_textedit.h",
        "imstb_truetype.h",
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
    includes = ["."],
    linkopts = ["-lSDL2 -lGL -ldl"],
)
