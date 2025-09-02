# mpacklog.cpp

[![Build](https://img.shields.io/github/actions/workflow/status/stephane-caron/mpacklog.cpp/bazel.yml?branch=main)](https://github.com/stephane-caron/mpacklog.cpp/actions)
[![Documentation](https://img.shields.io/badge/docs-online-brightgreen?logo=read-the-docs&style=flat)](https://stephane-caron.github.io/mpacklog.cpp/)
[![Coverage](https://coveralls.io/repos/github/stephane-caron/mpacklog.cpp/badge.svg?branch=main)](https://coveralls.io/github/stephane-caron/mpacklog.cpp?branch=main)
![C++ versions](https://img.shields.io/badge/C++-17/20-blue.svg?style=flat)
[![Release](https://img.shields.io/github/v/release/stephane-caron/mpacklog.cpp.svg?sort=semver)](https://github.com/stephane-caron/mpacklog.cpp/releases)

Log dictionaries to MessagePack files in C++.

## Installation

Add a git repository rule to your Bazel ``WORKSPACE``:

```python
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

http_archive(
    name = "mpacklog",
    sha256 = "d9931db7fff526f6eae1421e0b12eef7e153b43722191d85e79fe85c9438b3ec",
    strip_prefix = "mpacklog.cpp-3.2.0",
    url = "https://github.com/stephane-caron/mpacklog.cpp/archive/refs/tags/v3.2.0.tar.gz",
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

    palimpsest::Dictionary dict;
    dict("something") = "foo";

    for (unsigned bar = 0; bar < 1000u; ++bar) {
        dict("bar") = bar;
        logger.put(dict):
    }
}
```

## See also

* [jq](https://github.com/stedolan/jq): manipulate JSON series to add, remove or extend fields.
* [mpacklog.py](https://github.com/stephane-caron/mpacklog.py): Sibling Python project with an `mpacklog` command-line tool to manipulate MessagePack files.
* [rq](https://github.com/dflemstr/rq): transform from/to MessagePack, JSON, YAML, TOML, ...
