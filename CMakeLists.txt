cmake_minimum_required(VERSION 3.22)
project(mini-8)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
set(CMAKE_PREFIX_PATH)
set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME}  src/main.c
                                src/loader.c
                                src/renderer.c
                                src/random.c
                                src/core/chip.c
                                src/core/instructions.c)

find_package(SDL2 REQUIRED)

include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
                                