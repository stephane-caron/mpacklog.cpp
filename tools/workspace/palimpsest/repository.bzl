# -*- python -*-

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def palimpsest_repository(
        version = "2.4.0",
        sha256 = "d5c5381d8b3c77d46c4f1934fb0a1f0e7347d1f970e2a3119be00ae75f69b3d5"):
    """
    Download release archive from GitHub.

    Args:
        version: Version of the library to download.
        sha256: SHA-256 checksum of the downloaded archive.
    """
    http_archive(
        name = "palimpsest",
        url = "https://github.com/stephane-caron/palimpsest/archive/refs/tags/v{}.tar.gz".format(version),
        sha256 = sha256,
        strip_prefix = "palimpsest-{}".format(version),
    )
