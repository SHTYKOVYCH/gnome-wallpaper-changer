cmake_minimum_required(VERSION 3.0)

set(PROJECT wallparer)

project(${PROJECT})


set( HEADERS )

set(SOURCES
	main.c)

set( C_FLAGS "-g" )

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${G_FLAGS}" )

add_executable(${PROJECT} ${HEADERS} ${SOURCES} )

