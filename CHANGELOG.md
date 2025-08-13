# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [3.2.0] - 2025-08-13

### Added

- Add `Logger::buffer_size` getter

## [3.1.2] - 2025-08-11

### Changed

- Update palimpsest to 2.3.2

## [3.1.1] - 2024-12-17

### Added

- Bazel: Specify Bazel version to use a workspace rather than bzlmod
- CICD: Documentation workflow
- deps: Update palimpsest to 2.2.1

### Changed

- CICD: Update checkout action to v4
- docs: Don't show include files on class pages
- Bazel: Treat warnings as errors

## [3.1.0] - 2023-09-29

### Added

- Bazel: Find clang-format on various operating systems

### Changed

- Bazel: Compile build targets in optimized mode by default
- Bazel: Compile coverage and test targets in debug mode by default
- Python: Move all code to a separate [mpacklog.py](https://github.com/stephane-caron/mpacklog.py) project

## [3.0.0] - 2023-06-06

### Added

- (Python: Synchronous ``SyncLogger`` class)

### Changed

- CI: Update Bazelisk script
- (Python: Rename ``Logger`` to ``AsyncLogger``)
- (Python: Remove unused ``mypy_integration``)

## [2.1.0] - 2023-04-26

### Changed

- Make code compatible with macOS (thanks to @boragokbakan)

## [2.0.0] - 2022-09-01

### Added

- (Python: Dump log to CSV from the command line)
- (Python: Dump log to JSON from the command line)
- (Python: Dump log to Python script from the command line)
- (Python: List log fields from the command line)
- (Python: `Logger` implementation)
- (Python: `mpacklog` command-line tool)
- (Python: Unit tests for Python API)

## [1.0.0] - 2022-08-17

First release of the project.

[unreleased]: https://github.com/stephane-caron/mpacklog.cpp/compare/v3.2.0...HEAD
[3.2.0]: https://github.com/stephane-caron/mpacklog.cpp/compare/v3.1.2...v3.2.0
[3.1.2]: https://github.com/stephane-caron/mpacklog.cpp/compare/v3.1.1...v3.1.2
[3.1.1]: https://github.com/stephane-caron/mpacklog.cpp/compare/v3.1.0...v3.1.1
[3.1.0]: https://github.com/stephane-caron/mpacklog.cpp/compare/v3.0.0...v3.1.0
[3.0.0]: https://github.com/stephane-caron/mpacklog.cpp/compare/v2.1.0...v3.0.0
[2.1.0]: https://github.com/stephane-caron/mpacklog.cpp/compare/v2.0.0...v2.1.0
[2.0.0]: https://github.com/stephane-caron/mpacklog.cpp/compare/v1.0.0...v2.0.0
[1.0.0]: https://github.com/stephane-caron/mpacklog.cpp/releases/tag/v1.0.0
