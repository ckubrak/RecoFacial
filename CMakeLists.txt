cmake_minimum_required(VERSION 3.5)
project(tp2Imagenes)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -ggdb3 -g -O0")
set(SOURCE_FILES
        ppmloader/ppmloader.cpp
        ppmloader/ppmloader.h
        src/imagen.cpp
        src/imagen.h
        src/pca.h
        src/pca.cpp
        src/main.cpp
        )

add_executable(tp2 ${SOURCE_FILES})
