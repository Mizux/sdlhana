Github-CI:<br>
[![Build Status][amd64_linux_status]][amd64_linux_link]
[![Build Status][amd64_macos_status]][amd64_macos_link]
[![Build Status][arm64_macos_status]][arm64_macos_link]
[![Build Status][amd64_windows_status]][amd64_windows_link]<br>

[![Build Status][amd64_docker_status]][amd64_docker_link]

[amd64_linux_status]: ./../../actions/workflows/amd64_linux_cmake.yml/badge.svg
[amd64_linux_link]: ./../../actions/workflows/amd64_linux_cmake.yml
[amd64_macos_status]: ./../../actions/workflows/amd64_macos_cmake.yml/badge.svg
[amd64_macos_link]: ./../../actions/workflows/amd64_macos_cmake.yml
[arm64_macos_status]: ./../../actions/workflows/arm64_macos_cmake.yml/badge.svg
[arm64_macos_link]: ./../../actions/workflows/arm64_macos_cmake.yml
[amd64_windows_status]: ./../../actions/workflows/amd64_windows_cmake.yml/badge.svg
[amd64_windows_link]: ./../../actions/workflows/amd64_windows_cmake.yml

[amd64_docker_status]: ./../../actions/workflows/amd64_docker_cmake.yml/badge.svg
[amd64_docker_link]: ./../../actions/workflows/amd64_docker_cmake.yml

# Introduction
fork of http://sdlhana.nongnu.org/

# Build

To build the C++ project, as usual:

```sh
cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
CTEST_OUTPUT_ON_FAILURE=1 cmake --build build --config Release --target test
```

# Appendices

Few links on the subject...

## Resources

Project layout:
* [The Pitchfork Layout Revision 1 (cxx-pflR1)](https://github.com/vector-of-bool/pitchfork)

CMake:
* https://llvm.org/docs/CMakePrimer.html
* https://cliutils.gitlab.io/modern-cmake/
* https://cgold.readthedocs.io/en/latest/

# Contributing

The [CONTRIBUTING.md](./CONTRIBUTING.md) file contains instructions on how to
file the Contributor License Agreement before sending any pull requests (PRs).
Of course, if you're new to the project, it's usually best to discuss any
proposals and reach consensus before sending your first PR.

## License

GPL 2. See the LICENSE file for details.
