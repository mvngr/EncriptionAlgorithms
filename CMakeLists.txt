cmake_minimum_required(VERSION 3.14)

project(CipherConsoleServer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory("CipherConsoleServer")
add_subdirectory("CipherGuiClient")
add_subdirectory("CiphersLibrary")
