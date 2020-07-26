cmake_minimum_required(VERSION 3.13)
project(Kackgammon VERSION 1.0)

set(TARGET ${PROJECT_NAME})

set(PROJECT_HEADERS
	src/Die.h
	src/DieCup.h
	src/Player.h
	src/Die.h
	src/IdPushButton.h
	src/MainWindow.h)

set(PROJECT_SOURCES
	src/Main.cpp 
	src/Die.cpp 
	src/DieCup.cpp
	src/Player.cpp 
	src/Game.cpp
	src/IdPushButton.cpp
	src/MainWindow.cpp)

# for QT
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)

# c++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# taget executable
add_executable(${TARGET})
target_sources(${TARGET} PRIVATE ${PROJECT_HEADERS} ${PROJECT_SOURCES})

if(MSVC)
	target_compile_options(${TARGET} PRIVATE /W4 /WX)
else()
	target_compile_options(${TARGET} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

target_link_libraries(${TARGET} 
	PUBLIC
		Qt5::Core
		Qt5::Widgets
		Qt5::Gui)
