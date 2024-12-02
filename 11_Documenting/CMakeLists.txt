cmake_minimum_required(VERSION 3.16)
project(binsearch)

set(CMAKE_C_STANDARD 11)

# generating docs

find_package(Doxygen REQUIRED)

set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/../share/binsearch)
set(DOXYGEN_GENERATE_MAN YES)
set(DOXYGEN_GENERATE_TREEVIEW YES)
set(DOXYGEN_USE_MDFILE_AS_MAINPAGE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.md)
set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_FILE_PATTERNS *.c)

doxygen_add_docs(docs ${CMAKE_CURRENT_SOURCE_DIR}/src/binsearch.c ${CMAKE_CURRENT_SOURCE_DIR}/src/main.md ALL)

# generating locale

find_package(Gettext REQUIRED)

gettext_process_po_files(ru ALL INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}/../share/locale PO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/po/ru/binsearch.po)

# adding executable

add_executable(binsearch src/binsearch.c)

install(TARGETS binsearch DESTINATION ${CMAKE_INSTALL_PREFIX})
