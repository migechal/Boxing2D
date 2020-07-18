# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "imgui",
    srcs = ["imgui.cpp", "imgui_sdl.cpp", "imgui_draw.cpp", "imgui_widgets.cpp"],
    hdrs = ["imconfig.h", "imgui.h", "imgui_internal.h", "imgui_sdl.h", "imstb_rectpack.h", "imstb_textedit.h", "imstb_truetype.h", "imgui.cpp", "imgui_sdl.cpp", "imgui_draw.cpp", "imgui_widgets.cpp", "imgui_demo.cpp"],
    copts = ["-std=c++14"],
    visibility = ["//main:__pkg__"],
)