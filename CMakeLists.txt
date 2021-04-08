cmake_minimum_required(VERSION 3.7)

project(AndroidSimpleProject LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick LinguistTools REQUIRED)

set(H_FILES
    commonAlghorithms.h
    encryptionalgorithm.h
    ciphers/transpositioncipher.h
    ciphers/magicsquarecipher.h
    ciphers/caesarcipher.h
    ciphers/gronsfeldcipher.h
    ciphers/playfaircipher.h
    ciphers/giovanniportacipher.h

    dictionaries/dictionary.h
    dictionaries/digitdictionary.h
    dictionaries/cyrillicdictionary.h
)

set(CPP_FILES
    main.cpp
    encryptionalgorithm.cpp
    ciphers/transpositioncipher.cpp
    ciphers/magicsquarecipher.cpp
    ciphers/caesarcipher.cpp
    ciphers/gronsfeldcipher.cpp
    ciphers/playfaircipher.cpp
    ciphers/giovanniportacipher.cpp

    dictionaries/dictionary.cpp
    dictionaries/digitdictionary.cpp
    dictionaries/cyrillicdictionary.cpp
)

set(PROJECT_SOURCES
        ${CPP_FILES}
        ${H_FILES}
        qml.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(AndroidSimpleProject
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(AndroidSimpleProject SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(AndroidSimpleProject
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(AndroidSimpleProject
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(AndroidSimpleProject PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)
