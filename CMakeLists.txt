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

if (NOT SCILOG_DIR)
	if (WIN32)
		set(SCILOG_DIR "$ENV{HOME}\\scilog")
	endif (WIN32)
	if (UNIX)
		set(SCILOG_DIR "$ENV{HOME}/scilog")
	endif (UNIX)
endif (NOT SCILOG_DIR)

configure_file(config.hpp.in config.hpp)
configure_file(scilog.conf.in scilog.conf)

unset(SCILOG_DIR CACHE)

set(TARGET_LOCAL_H
config.hpp
cli
core)

file(GLOB_RECURSE TARGET_SRC cli/*.cpp core/*.cpp)

project(scilog)

add_executable(scilog ${TARGET_SRC} main.cpp scilog.conf)
target_link_libraries(scilog boost_system-mt boost_date_time-mt boost_filesystem-mt)

install(TARGETS scilog RUNTIME DESTINATION bin)
install(FILES scilog.conf DESTINATION etc COMPONENT config)
