# AGENTS.md

## C++ Build & Test

- **Build**: `cmake -S . -B cmake_build` (creates the Ninja build tree). If you want a debug build, add `-D CMAKE_BUILD_TYPE=Debug`.
- **Compile**: `ninja -C cmake_build` or `cmake --build cmake_build`.
- **Run all tests**: `ninja -C cmake_build test` or `ctest -C cmake_build`.
- **Run a single test**: either run the executable directly, e.g. `./cmake_build/cc/23_merge_k_sorted_list`, or use CTest: `ctest -C cmake_build -R 23_merge_k_sorted_list`.
- **Run tests in parallel**: `ctest -C cmake_build -j <n>`.
- **Enable coverage**: `cmake -S . -B cmake_build -D ENABLE_COVERAGE=ON` then build and run tests. Coverage data will be in the build tree.
- **Address sanitizer**: Enabled automatically on Unix builds (via `-fsanitize=address`). If you want to disable it, add `-D CMAKE_CXX_FLAGS="${CMAKE_CXX_FLAGS} -DNO_ASAN"`.

## Project structure

- The top‑level `CMakeLists.txt` pulls in the `cc` subdirectory.
- Each `.cc` file in `cc/` is compiled into an executable with the same name (without the `.cc` extension). These executables automatically link against GoogleTest and GoogleBenchmark.
- Tests use `enable_testing()` and `add_test()`, so they are discoverable by CTest.

## Toolchain

- Requires CMake ≥ 3.19 and Ninja (or Make). `cmake` will fetch GoogleTest and GoogleBenchmark automatically.
- The compiler is set to `clang++` by default (`SET(CXX "clang++")`).
- Build flags include `-O3`, `-Wall`, `-Wextra`, and address sanitizer on Unix.

## Notes

- The repository contains many other language directories (Go, Rust, TS, etc.) but they are **not** built by CMake. Use their native tooling (e.g., `go test`, `cargo test`, `npm test`) for those.
- `make` is a thin wrapper that simply runs `ninja -C build`.
- If you encounter missing dependencies, ensure your system has a C++ compiler that supports C++17 and the required build tools.

## Quick reference

```sh
# Build & test
cmake -S . -B cmake_build && ninja -C cmake_build test

# Run single test
./cmake_build/cc/23_merge_k_sorted_list

# Coverage
cmake -S . -B cmake_build -D ENABLE_COVERAGE=ON && ninja -C cmake_build test
```
