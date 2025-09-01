# -*- python -*-
#
# Copyright 2022 Stéphane Caron

load("//tools/lint:lint.bzl", "add_lint_tests")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "circular_buffer",
    hdrs = [
        "CircularBuffer.h",
    ],
    include_prefix = "mpacklog",
    deps = [
        "@spdlog",
    ],
)

cc_library(
    name = "logger",
    hdrs = [
        "Logger.h",
    ],
    include_prefix = "mpacklog",
    srcs = [
        "Logger.cpp",
    ],
    copts = [
        "-pthread",
    ],
    linkopts = [
        "-pthread",
    ],
    deps = [
        ":circular_buffer",
        "@palimpsest",
    ],
)

cc_library(
    name = "delta_logger",
    hdrs = [
        "DeltaLogger.h",
    ],
    include_prefix = "mpacklog",
    srcs = [
        "DeltaLogger.cpp",
    ],
    copts = [
        "-pthread",
    ],
    linkopts = [
        "-pthread",
    ],
    deps = [
        ":logger",
        "@palimpsest",
    ],
)

cc_library(
    name = "mpacklog",
    deps = [
        ":circular_buffer",
        ":delta_logger",
        ":logger",
    ],
)

add_lint_tests()
