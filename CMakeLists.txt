cmake_minimum_required(VERSION 3.13)
project(Kackgammon VERSION 1.0)
set(TARGET "Main")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(CMAKE_CURRENT_SOURCE_DIR "./src/")

add_executable(${TARGET})
target_sources(${TARGET}
	PRIVATE 
		src/Main.cpp 
		src/Die.cpp 
		src/Die.h
		src/Player.cpp 
		src/Player.h
		src/Game.cpp
		src/Game.h)

if(MSVC)
	target_compile_options(${TARGET} PRIVATE /W4 /WX)
else()
	target_compile_options(${TARGET} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
