load("@rules_cc//cc:defs.bzl", "cc_library")
cc_library(
    name = "Sources",
    hdrs = [
        "headers/input.h",
        "headers/player.h",
        "headers/init.h",
        "headers/gamebase.h",
        "headers/debugmodule.h",
    ],
    srcs = [
        "input.cpp",
        "init.cpp",
        "debugmodule.cpp",
        "gamebase.cpp",
    ],
    defines = [
        "REENTRANT",
    ],
    visibility = ["//main:__pkg__"],
)