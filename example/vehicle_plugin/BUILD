# add module from parent of parent directory
load("@rules_cc//cc:cc_binary.bzl", "cc_binary")
cc_binary(
    name = "vehicle",
    srcs = glob([
        "*.cpp",
        "*.hpp",
        "ifc/*.h",
    ]),
    copts = [
        "/MP",
        "/Od",
    ],
    linkshared = 1,
    deps = [
        "@incl//comm:comm_static",
        "@incl//glm",
        "@incl//ot",
        "@incl//v8",
    ],
)
