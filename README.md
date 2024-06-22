
## Get WEB library
```
PLATFORM             ?= PLATFORM_WEB
RAYLIB_RELEASE_PATH  ?= $(RAYLIB_SRC_PATH)/web
emsdk activate latest --permanent to get versions of tools

PYTHON_PATH        := $(EMSDK_PATH)/python/3.9.2-nuget-64bit
NODE_PATH          := $(EMSDK_PATH)/node/16.20.0-64bit/bin

make -e PLATFORM=PLATFORM_WEB -B

creates libraylib.a in web folder
```

## Compile to WASM
```shell
emcc -o tetris.html main.cpp colors.cpp grid.cpp position.cpp -Wall -std=c++17 -D_DEFAULT_SOURCE -Wno-missing-braces -Wunused-result -Os -I. -I C:/Users/david/.vcpkg-clion/vcpkg/buildtrees/raylib/src/5.0-24e38c87d8.clean/src -I C:/Users/david/.vcpkg-clion/vcpkg/buildtrees/raylib/src/5.0-24e38c87d8.clean/src/external -L. -L C:/Users/david/.vcpkg-clion/vcpkg/buildtrees/raylib/src/5.0-24e38c87d8.clean/src -s USE_GLFW=3 -s ASYNCIFY -s TOTAL_MEMORY=67108864 -s FORCE_FILESYSTEM=1 --shell-file C:/Users/david/.vcpkg-clion/vcpkg/buildtrees/raylib/src/5.0-24e38c87d8.clean/src/shell.html C:/Users/david/.vcpkg-clion/vcpkg/buildtrees/raylib/src/5.0-24e38c87d8.clean/src/web/libraylib.a -DPLATFORM_WEB -s "EXPORTED_FUNCTIONS=['_free','_malloc','_main']" -s EXPORTED_RUNTIME_METHODS=ccall
```
