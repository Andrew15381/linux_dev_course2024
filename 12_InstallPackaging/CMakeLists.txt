cmake_minimum_required(VERSION 3.16)
project(binsearch)

set(CMAKE_C_STANDARD 11)

# generating docs

find_package(Doxygen REQUIRED)

set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/../share/binsearch)
set(DOXYGEN_GENERATE_TREEVIEW YES)
set(DOXYGEN_USE_MDFILE_AS_MAINPAGE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.md)
set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_FILE_PATTERNS *.c *.h)

doxygen_add_docs(docs ${CMAKE_CURRENT_SOURCE_DIR}/src/binsearch.c ${CMAKE_CURRENT_SOURCE_DIR}/src/binsearch.h ${CMAKE_CURRENT_SOURCE_DIR}/src/main.md ALL)

add_custom_command(
    OUTPUT binsearch.3
    POST_BUILD
    COMMAND tar cvzf ${CMAKE_INSTALL_PREFIX}/../share/man/man3/binsearch.3.gz ${CMAKE_CURRENT_SOURCE_DIR}/binsearch.3
)

add_custom_target(run ALL
    DEPENDS binsearch.3)

# generating locale

find_package(Gettext REQUIRED)

gettext_process_po_files(ru ALL INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}/../share/locale PO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/po/ru/binsearch.po)

# adding executable

add_executable(binsearch src/binsearch.c)

target_compile_definitions(binsearch PUBLIC INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}")

install(TARGETS binsearch DESTINATION ${CMAKE_INSTALL_PREFIX})

# adding tests

include(CTest)
enable_testing()

add_executable(tests tests/tests.c)

set(TESTS
    "roman_to_int"
    "int_to_roman"
    "int_to_str_decimal"
    "int_to_str_roman"
)

foreach(TEST_NAME IN LISTS TESTS)
    add_test(NAME ${TEST_NAME} COMMAND tests ${TEST_NAME})
endforeach()
