load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
        name= "main",
        srcs = ["main.cpp"],
        copts = ["-std=c++14"],
        linkopts = ["-lSDL2"],
        deps = ["//src:imgui"],
)