# -*- python -*-

load("//tools/lint:lint.bzl", "add_lint_tests")

package(default_visibility = ["//visibility:public"])

cc_test(
    name = "circular_buffer",
    srcs = ["CircularBufferTest.cpp"],
    deps = [
        "//mpacklog",
        "@eigen",
        "@googletest//:main",
    ],
)

cc_test(
    name = "delta_logger",
    srcs = ["DeltaLoggerTest.cpp"],
    deps = [
        "//mpacklog",
        "@eigen",
        "@googletest//:main",
    ],
)

cc_test(
    name = "logger",
    srcs = ["LoggerTest.cpp"],
    deps = [
        "//mpacklog",
        "@eigen",
        "@googletest//:main",
    ],
)

add_lint_tests()
