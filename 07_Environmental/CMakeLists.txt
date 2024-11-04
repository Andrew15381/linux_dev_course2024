cmake_minimum_required(VERSION 3.16)
project(environmental)

set(CMAKE_C_STANDARD 11)

option(ENABLE_READLINE "Enable reading through readline" ON)

find_library(LIBRHASH rhash)

if(NOT LIBRHASH)
    message(FATAL_ERROR "Lib rhash is required")
endif()

find_library(LIBREADLINE readline)

if(NOT LIBREADLINE)
    message(WARNING "Lib readline is not found, using getline")
    set(ENABLE_READLINE OFF)
endif()

add_executable(rhasher rhasher.c)

target_link_libraries(rhasher PRIVATE ${LIBRHASH})

if(ENABLE_READLINE)
    target_compile_definitions(rhasher PRIVATE ENABLE_READLINE)
    target_link_libraries(rhasher PRIVATE ${LIBREADLINE})
endif()
