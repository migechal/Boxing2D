load("@rules_cc//cc:defs.bzl", "cc_library")
cc_library(
    name = "Sources",
    srcs = [
        "input.cpp",
        "init.cpp",
        "debugmodule.cpp",
        "gamebase.cpp",
    ],
    defines = [
        "REENTRANT",
    ],
    deps = [
        "//headers:HeaderFiles",
    ],
    visibility = ["//main:__pkg__"],
)