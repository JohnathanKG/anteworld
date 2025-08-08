load("@rules_cc//cc:cc_library.bzl", "cc_library")

cc_library(
    name = "ot",
    srcs = glob(
        include = [
            "*.cpp",
            "**/*.cpp",
        ],
    ),
    hdrs = glob(
        include = [
            "*.h",
            "**/*.h",
        ],
    ),
    copts = [
        "/MP",
        "/Od",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@incl//comm:comm_static",
        "@incl//glm",
    ],
)
