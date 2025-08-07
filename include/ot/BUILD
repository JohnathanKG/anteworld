load("@rules_cc//cc:cc_library.bzl", "cc_library")

cc_library(
    name = "ot",
    srcs = glob(
        include = [
            "*.cpp",
            "**/*.cpp",
        ]
    ),
    hdrs = glob(
        include = [
            "*.h",
            "**/*.h",
        ]
    ),
    deps = [
        "@incl//comm:comm_static",
        "@incl//glm:glm",
    ],
    visibility = ["//visibility:public"],
)