load("@rules_cc//cc:defs.bzl", "cc_library")
cc_library(
    name = "Sources",
    srcs = glob(["*.cpp"]),
    defines = [
        "REENTRANT",
    ],
    deps = [
        "//headers:HeaderFiles",
    ],
    visibility = ["//main:__pkg__"],
)