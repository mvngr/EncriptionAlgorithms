cmake_minimum_required(VERSION 3.14)

project(CiphersLibrary LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

set(H_FILES
    CiphersLibrary_global.h

    commonAlghorithms.h

    ciphers/encryptionalgorithm.h
    ciphers/transpositioncipher.h
    ciphers/magicsquarecipher.h
    ciphers/caesarcipher.h
    ciphers/gronsfeldcipher.h
    ciphers/playfaircipher.h
    ciphers/giovanniportacipher.h
    ciphers/vigenerecipher.h
    ciphers/trithemiuscipher.h
    ciphers/spiralcipher.h

    dictionaries/dictionary.h
    dictionaries/digitdictionary.h
    dictionaries/cyrillicdictionary.h
)

set(CPP_FILES

    ciphers/encryptionalgorithm.cpp
    ciphers/transpositioncipher.cpp
    ciphers/magicsquarecipher.cpp
    ciphers/caesarcipher.cpp
    ciphers/gronsfeldcipher.cpp
    ciphers/playfaircipher.cpp
    ciphers/giovanniportacipher.cpp
    ciphers/vigenerecipher.cpp
    ciphers/trithemiuscipher.cpp
    ciphers/spiralcipher.cpp

    dictionaries/dictionary.cpp
    dictionaries/digitdictionary.cpp
    dictionaries/cyrillicdictionary.cpp
)

add_library(CiphersLibrary SHARED
    ${H_FILES}
    ${CPP_FILES}
)

target_link_libraries(CiphersLibrary PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(CiphersLibrary PRIVATE CIPHERSLIBRARY_LIBRARY)
