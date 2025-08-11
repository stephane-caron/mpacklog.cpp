# mpacklog.cpp

[![Build](https://img.shields.io/github/actions/workflow/status/stephane-caron/mpacklog.cpp/bazel.yml?branch=main)](https://github.com/stephane-caron/mpacklog.cpp/actions)
[![Coverage](https://coveralls.io/repos/github/stephane-caron/mpacklog.cpp/badge.svg?branch=main)](https://coveralls.io/github/stephane-caron/mpacklog.cpp?branch=main)
[![Documentation](https://img.shields.io/badge/docs-online-brightgreen?logo=read-the-docs&style=flat)](https://stephane-caron.github.io/mpacklog.cpp/)
![C++ version](https://img.shields.io/badge/C++-17/20-blue.svg?style=flat)
[![C++ release](https://img.shields.io/github/v/release/stephane-caron/mpacklog.cpp.svg?sort=semver)](https://github.com/stephane-caron/mpacklog.cpp/releases)

Log dictionaries to MessagePack files in C++.

## Installation

Add a git repository rule to your Bazel ``WORKSPACE``:

```python
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

http_archive(
    name = "mpacklog",
    sha256 = "389cbd249607f1d0a2bbf6d11cbf0690604966e29a8e75e50160cf0faab068c7",
    strip_prefix = "mpacklog.cpp-3.1.0",
    url = "https://github.com/stephane-caron/mpacklog.cpp/archive/refs/tags/v3.1.0.tar.gz",
)

load("@mpacklog//tools/workspace:default.bzl", add_mpacklog_repositories = "add_default_repositories")

# This adds dependencies such as @palimpsest for building mpacklog targets
add_mpacklog_repositories()
```

You can then use the ``@mpacklog`` dependency in your C++ targets.

## Usage

The library is multi-threaded. Add messages to the log using the [`put`](https://scaron.info/doc/mpacklog/classmpacklog_1_1Logger.html#af0c278a990b1275b306e89013bb1fac6) function, they will be written to file in the background.

```cpp
#include <mpacklog/Logger.h>
#include <palimpsest/Dictionary.h>

int main() {
    mpacklog::Logger logger("output.mpack");

    for (unsigned bar = 0; bar < 1000u; ++bar) {
        palimpsest::Dictionary dict;
        dict("foo") = bar;
        dict("something") = "else";
        logger.put(dict):
    }
}
```

## See also

* [mpacklog.py](https://github.com/stephane-caron/mpacklog.py): Sibling Python project with an `mpacklog` command-line tool to manipulate MessagePack files.
* [`jq`](https://github.com/stedolan/jq): manipulate JSON series to add, remove or extend fields.
* [`rq`](https://github.com/dflemstr/rq): transform from/to MessagePack, JSON, YAML, TOML, ...
