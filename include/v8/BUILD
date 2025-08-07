load("@rules_cc//cc:cc_library.bzl", "cc_library")

cc_library(
    name = "v8",
    hdrs = glob(
        include = [
            "*.h",
        ]
    ),
    copts = [
        "/MP",
        "/Od"
    ],
    visibility = ["//visibility:public"],
)