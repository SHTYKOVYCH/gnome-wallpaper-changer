cmake_minimum_required(VERSION 3.0)

set(PROJECT wallparer_cpp)

project(${PROJECT})


#set( HEADERS 
#	definitions.hpp
#	Exception.hpp
#	SystemUser.hpp
#	WallpaperKeeper.hpp)

include_directories("./headers")

set(SOURCES
	main.cpp
	./src/Exception.cpp
	./src/SystemUser.cpp
	./src/WallpaperKeeper.cpp)

set( CXX_FLAGS "-g -O2" )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_FLAGS}" )

add_executable(${PROJECT} ${HEADERS} ${SOURCES} )

