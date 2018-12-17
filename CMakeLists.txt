cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set (CMAKE_CXX_STANDARD 14)

project (gameoflife_project CXX)

#file globing
file(GLOB_RECURSE sources src/*.cpp src/*.h)
file(GLOB_RECURSE data resources/*)

add_executable(gameoflife ${sources} ${data})

#copy resources to build directory
file(COPY ${data} DESTINATION resources)

#armadillo library
find_package(Armadillo REQUIRED)

#include the necessary libraries
find_package(SFML 2 REQUIRED system window graphics)
find_package(TGUI REQUIRED)

if(NOT SFML_FOUND)
    message(FATAL_ERROR "Could not find SFML")
endif()

if(NOT TGUI_FOUND)
    message(FATAL_ERROR "Could not find TGUI")
endif()

if(NOT ARMADILLO_FOUND)
	message(FATAL_ERROR "Could not find armadillo")
endif()

include_directories(${SFML_INCLUDE_DIR})
include_directories(${TGUI_INCLUDE_DIR})
include_directories(${ARMADILLO_INCLUDE_DIRS})

target_link_libraries(gameoflife ${SFML_LIBRARIES} ${TGUI_LIBRARY} ${ARMADILLO_LIBRARIES})
