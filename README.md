# Tetris made in raylib with C++

## Compile to WASM

### Get WEB library

```shell
PLATFORM             ?= PLATFORM_WEB
RAYLIB_RELEASE_PATH  ?= $(RAYLIB_SRC_PATH)/web
emsdk activate latest --permanent #to get versions of tools

PYTHON_PATH        := $(EMSDK_PATH)/python/3.9.2-nuget-64bit
NODE_PATH          := $(EMSDK_PATH)/node/16.20.0-64bit/bin

make -e PLATFORM=PLATFORM_WEB -B

creates libraylib.a in web folder
```

### Compile to WASM

```shell
emcc -o wasmOUT/tetris.html main.cpp colors.cpp grid.cpp position.cpp block.cpp tetrominoes.cpp game.cpp -Wall -std=c++17 -D_DEFAULT_SOURCE -Wno-missing-braces -Wunused-result -Os -I. -I C:/Users/david/.vcpkg-clion/vcpkg/buildtrees/raylib/src/5.0-24e38c87d8.clean/src -s USE_GLFW=3 -s ASYNCIFY -s TOTAL_MEMORY=134217728 -s FORCE_FILESYSTEM=1 --shell-file C:/Users/david/.vcpkg-clion/vcpkg/buildtrees/raylib/src/5.0-24e38c87d8.clean/src/shell.html H:\C++\raylib-tetris-oop\lib\libraylib.a -DPLATFORM_WEB -s "EXPORTED_FUNCTIONS=['_free','_malloc','_main']" -s EXPORTED_RUNTIME_METHODS=ccall --preload-file Sounds --preload-file Font/monogram.ttf


```

<details>
  <summary>Explanations</summary>

| **Command**                                           | **Explanation**                                                                                                        |
|-------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------|
| `emcc`                                                | The Emscripten compiler                                                                                                |
| `-o tetris.html`                                      | Outputs html                                                                                                           |
| `main.cpp ...`                                        | The C++ source files to be compiled.                                                                                   |
| `-Wall`                                               | Enables all compiler's warning messages.                                                                               |
| `-std=c++17`                                          | Sets the C++ standard to C++17.                                                                                        |
| `-D_DEFAULT_SOURCE`                                   | Defines the `_DEFAULT_SOURCE` macro, used for feature test macros or other purposes in the code.                       |
| `-Wno-missing-braces`                                 | Disables warnings about missing braces in initialization lists.                                                        |
| `-Wunused-result`                                     | Warns if a result from a function call is unused.                                                                      |
| `-Os`                                                 | Optimizes the code for size.                                                                                           |
| `-I.`                                                 | Adds the current directory (.) to the list of directories to be searched for header files.                             |
| `-s USE_GLFW=3`                                       | Tells Emscripten to use GLFW version 3, an open-source library for creating windows, contexts, and handling input.     |
| `-s ASYNCIFY`                                         | Enables asyncify, allowing for asynchronous functions in the compiled WebAssembly code.                                |
| `-s TOTAL_MEMORY=67108864`                            | Sets the total memory size for the WebAssembly module to 64MB.                                                         |
| `-s FORCE_FILESYSTEM=1`                               | Ensures that Emscripten's filesystem support is included.                                                              |
| `--shell-file /src/shell.html`                        | Uses the specified shell HTML file as a template for the output HTML file.                                             |
| `/web/libraylib.a`                                    | Links the `libraylib.a` library file.                                                                                  |
| `-DPLATFORM_WEB`                                      | Defines the `PLATFORM_WEB` macro, to compile specifically to web platform.                                             |
| `-s "EXPORTED_FUNCTIONS=['_free','_malloc','_main']"` | Exports the specified functions (`_free`, `_malloc`, `_main`) from the WebAssembly module for calling from JavaScript. |
| `-s EXPORTED_RUNTIME_METHODS=ccall`                   | Exports the `ccall` method, allowing C functions to be called from JavaScript.                                         |

</details>
