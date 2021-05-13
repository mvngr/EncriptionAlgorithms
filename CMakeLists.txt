cmake_minimum_required(VERSION 3.14)

project(EncriptionAlgorithms)

if(NOT ANDROID)
    add_subdirectory("CipherConsoleServer")
    add_subdirectory("CiphersLibrary")
endif()
add_subdirectory("CipherGuiClient")
