cmake_minimum_required(VERSION 4.3)
project(ayed_libreria_listas_void_primitivas C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

set(SOURCES
        src/lista.c
        src/nodo.c
        src/main.c
)

add_executable(ayed_libreria_listas_void_primitivas ${SOURCES})
