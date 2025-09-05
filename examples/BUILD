# -*- python -*-

load("//tools/lint:lint.bzl", "add_lint_tests")

package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "delta_compression",
    srcs = ["delta_compression.cpp"],
    deps = [
        "//mpacklog:delta_logger",
        "//mpacklog:logger",
        "@eigen",
    ],
)

add_lint_tests()