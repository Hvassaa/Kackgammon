cmake_minimum_required(VERSION 3.13)
project(Kackgamon VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(CMAKE_CURRENT_SOURCE_DIR "./src/")

add_executable(Main)
target_sources(Main 
	PRIVATE 
		src/Main.cpp 
		src/Die.cpp 
		src/Die.h
		src/Player.cpp 
		src/Player.h
		src/Game.cpp
		src/Game.h)
