cmake_minimum_required(VERSION 3.13)

project(lua_vm_obfuscator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(lua_vm_obfuscator
    src/main.cpp
)
