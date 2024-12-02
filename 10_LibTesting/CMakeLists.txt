cmake_minimum_required(VERSION 3.16)
project(libtesting)

set(CMAKE_C_STANDARD 99)

set(SOURCES
    src/buf.h
    src/buf.c
)

add_library(buf SHARED ${SOURCES})
target_compile_options(buf PUBLIC -fprofile-arcs -ftest-coverage)
target_link_options(buf PUBLIC -coverage)

include(CTest)
enable_testing()

set(TEST_SOURCES
    tests.c
)

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PUBLIC buf)

set(TESTS
    "capacity_init" 
    "size_init" 
    "size_1" 
    "value" 
    "clear" 
    "clear_not_free" 
    "free" 
    "clear_empty" 
    "clear_nop" 
    "size_10000" 
    "match_10000" 
    "grow_1000"
    "size_0_grow"
    "trunc_100"
    "size_4"
    "pop_3"
    "size_3"
    "pop_2"
    "pop_1"
    "pop_0"
    "size_0_pop"
)

foreach(TEST_NAME IN LISTS TESTS)
    add_test(NAME ${TEST_NAME} COMMAND tests ${TEST_NAME})
endforeach()

