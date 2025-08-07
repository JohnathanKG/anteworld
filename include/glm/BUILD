load("@rules_cc//cc:cc_library.bzl", "cc_library")

cc_library(
    name = "glm",
    srcs = glob(
        include = [
            "*.hpp",
            "**/*.inl",
            "**/*.h",
            "**/*.hpp",
        ],
    ),
    copts = [
        "/MP",
        "/Od"
    ],
    visibility = ["//visibility:public"],
)