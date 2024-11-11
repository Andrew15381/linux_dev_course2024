cmake_minimum_required(VERSION 3.16)
project(binsearch)

set(CMAKE_C_STANDARD 11)

find_package(Gettext REQUIRED)

gettext_process_po_files(ru ALL INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}/../share/locale PO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/po/ru/binsearch.po)

add_executable(binsearch src/binsearch.c)

install(TARGETS binsearch DESTINATION ${CMAKE_INSTALL_PREFIX})
