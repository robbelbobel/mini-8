cmake_minimum_required(VERSION 3.22)

project(mini-8)

add_executable(${PROJECT_NAME}  src/main.c
                                src/loader.c
                                src/core/chip.c
                                src/core/instructions.c)
