load("@rules_cc//cc:defs.bzl", "cc_binary")

filegroup(
    name = "config",
    srcs = [
        "settings/config.json",
    ],
)

filegroup(
    name = "assets",
    srcs = glob([
        "assets/**/*",
    ]),
)

cc_binary(
    name = "game",
    srcs = [
        "main.cpp",
    ],
    args = ["menu"],
    copts = [
        "-std=c++14",
        "-Wformat",
    ],
    data = [
        ":assets",
        ":config",
    ],
    defines = [
        "IMGUI_IMPL_OPENGL_LOADER_GL3W",
        "REENTRANT",
    ],
    linkopts = ["-lSDL2 -lGL -ldl"],
    deps = [
        "//Cust_func:func_lib",
        "//imgui:imgui_lib",
    ],
)
