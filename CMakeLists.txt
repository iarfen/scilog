set(TARGET_DIRECTORIES
cli
core)

set(TARGET_LIBRARIES
cafi
boost_system-mt
boost_date_time-mt
boost_filesystem-mt
conf)

set(PACKAGE_NAME "scilog")
set(PACKAGE_VERSION "1.0")

set(PACKAGE_AUTHOR "Ismael Correa C.")
set(PACKAGE_VENDOR "ismaelc")

set(PACKAGE_BUGREPORT "ismael.correa.castro@gmail.com")
set(PACKAGE_WEBSITE "https://www.github.com/Iarfen/scilog")

set(PACKAGE_YEAR "2018")

cmake_minimum_required(VERSION 3.8.2)

include_directories("${CMAKE_INSTALL_PREFIX}/include" .)
link_directories("${CMAKE_INSTALL_PREFIX}/lib")

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

#set(TARGET_SRC_MATCH ${TARGET_DIRECTORIES})
#list(TRANSFORM ${TARGET_SRC_MATCH} APPEND /*.cpp)
#list(APPEND TARGET_SRC_MATCH "${TARGET_DIRECTORIES}/*.cpp")
file(GLOB_RECURSE TARGET_SRC main.cpp cli/*.cpp core/*.cpp)

project(scilog)

add_executable(scilog ${TARGET_SRC} scilog.conf)
target_link_libraries(scilog ${TARGET_LIBRARIES})

install(TARGETS scilog RUNTIME DESTINATION bin)
install(FILES scilog.conf DESTINATION etc COMPONENT config)
