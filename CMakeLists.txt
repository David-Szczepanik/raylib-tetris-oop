#cmake_minimum_required(VERSION 3.28)
#project(raylib-tetris-oop)
#
#set(CMAKE_CXX_STANDARD 17)
#
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -E")
#
#find_package(raylib CONFIG REQUIRED)
#
#add_executable(raylib-tetris-oop main.cpp
#)
#
#target_link_libraries(raylib-tetris-oop PRIVATE raylib)


# Preprocess
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.28)
project(raylib_tetris_oop)

# Ensure the toolchain file is used
if (DEFINED CMAKE_TOOLCHAIN_FILE)
    include(${CMAKE_TOOLCHAIN_FILE})
endif ()

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_PREFIX_PATH "/path/to/raylib")
find_package(raylib CONFIG REQUIRED)

# Collect include directories
include_directories(${raylib_INCLUDE_DIRS})

set(SOURCES
        main_page.cpp
        main.cpp
        grid.cpp
        position.cpp
        colors.cpp
        block.cpp
        tetrominoes.cpp
        game.cpp
)

set(HEADERS
        grid.h
        block.h
        position.h
        colors.h
        game.h
)

# Add custom command to preprocess .cpp files to .i files
foreach (source_file ${SOURCES})
    get_filename_component(file_basename ${source_file} NAME_WE)
    add_custom_command(
            OUTPUT ${CMAKE_BINARY_DIR}/${file_basename}.i
            COMMAND ${CMAKE_CXX_COMPILER} -E ${CMAKE_SOURCE_DIR}/${source_file} -o ${CMAKE_BINARY_DIR}/${file_basename}.i -I${raylib_INCLUDE_DIRS}
            DEPENDS ${source_file} ${HEADERS}
            COMMENT "Preprocessing ${source_file} to ${file_basename}.i"
    )
    list(APPEND PREPROCESSED_FILES ${CMAKE_BINARY_DIR}/${file_basename}.i)
endforeach ()

add_custom_target(preprocess ALL DEPENDS ${PREPROCESSED_FILES})

add_executable(raylib-tetris-oop ${SOURCES} ${HEADERS}
)

target_link_libraries(raylib-tetris-oop PRIVATE raylib)
