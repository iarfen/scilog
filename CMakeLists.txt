cmake_minimum_required(VERSION 3.8.2)

include_directories(C:/Programas/MSYS2/mingw64/include .)
link_directories(C:/Programas/MSYS2/mingw64/lib)

set(CMAKE_CXX_COMPILER C:/Programas/MSYS2/mingw64/bin/g++.exe)

set(PACKAGE_NAME "scilog")
set(PACKAGE_VERSION 1.0)

set(PACKAGE_AUTHOR "Ismael Correa C.")
set(PACKAGE_VENDOR "ismaelc")

set(PACKAGE_BUGREPORT "ismael.correa.castro@gmail.com")
set(PACKAGE_WEBSITE "https://www.github.com/Iarfen/scilog")

configure_file(config.hpp.in config.hpp)

set(TARGET_LOCAL_H
config.hpp
cli/create.hpp
cli/help.hpp
cli/list.hpp
cli/summary.hpp
cli/version.hpp
core/entry.hpp
core/xml_parser.hpp)

set(TARGET_SRC
cli/create.cpp
cli/help.cpp
cli/list.cpp
cli/summary.cpp
cli/version.cpp
main.cpp
core/entry.cpp
core/xml_parser.cpp)

project(scilog)

add_executable(scilog ${TARGET_SRC} main.cpp)
target_link_libraries(scilog)

install(TARGETS scilog RUNTIME DESTINATION bin)
