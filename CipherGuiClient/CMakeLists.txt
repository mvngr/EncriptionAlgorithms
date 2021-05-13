cmake_minimum_required(VERSION 3.7)
if(NOT ANDROID)
    set(PROJECT_NAME CipherGuiClient)
else()
    set(PROJECT_NAME CipherGuiClientAndroid)
endif()
project(${PROJECT_NAME} LANGUAGES CXX)

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

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick LinguistTools Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick LinguistTools Network REQUIRED)

if(ANDROID)
    set(ADDICTION_H
        ../CiphersLibrary/CiphersLibrary_global.h

        ../CiphersLibrary/commonAlghorithms.h

        ../CiphersLibrary/ciphers/encryptionalgorithm.h
        ../CiphersLibrary/ciphers/transpositioncipher.h
        ../CiphersLibrary/ciphers/magicsquarecipher.h
        ../CiphersLibrary/ciphers/caesarcipher.h
        ../CiphersLibrary/ciphers/gronsfeldcipher.h
        ../CiphersLibrary/ciphers/playfaircipher.h
        ../CiphersLibrary/ciphers/giovanniportacipher.h
        ../CiphersLibrary/ciphers/vigenerecipher.h
        ../CiphersLibrary/ciphers/trithemiuscipher.h

        ../CiphersLibrary/dictionaries/dictionary.h
        ../CiphersLibrary/dictionaries/digitdictionary.h
        ../CiphersLibrary/dictionaries/cyrillicdictionary.h
        )
endif()

set(H_FILES
    cipherstcpclient.h

    ${ADDICTION_H}
    )

if(ANDROID)
    set( ADDICTION_CPP
        ../CiphersLibrary/ciphers/encryptionalgorithm.cpp
        ../CiphersLibrary/ciphers/transpositioncipher.cpp
        ../CiphersLibrary/ciphers/magicsquarecipher.cpp
        ../CiphersLibrary/ciphers/caesarcipher.cpp
        ../CiphersLibrary/ciphers/gronsfeldcipher.cpp
        ../CiphersLibrary/ciphers/playfaircipher.cpp
        ../CiphersLibrary/ciphers/giovanniportacipher.cpp
        ../CiphersLibrary/ciphers/vigenerecipher.cpp
        ../CiphersLibrary/ciphers/trithemiuscipher.cpp

        ../CiphersLibrary/dictionaries/dictionary.cpp
        ../CiphersLibrary/dictionaries/digitdictionary.cpp
        ../CiphersLibrary/dictionaries/cyrillicdictionary.cpp
        )
endif()

set(CPP_FILES
    main.cpp

    cipherstcpclient.cpp

    ${ADDICTION_CPP}
    )


set(PROJECT_SOURCES
    ${CPP_FILES}
    ${H_FILES}
    qml.qrc
    )

include_directories("../CiphersLibrary")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
        )
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
            )
    else()
        add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES}
            )
    endif()
endif()

target_compile_definitions(${PROJECT_NAME}
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
if(ANDROID)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Network)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Network CiphersLibrary)
endif()
