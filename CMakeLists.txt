# CMakeList.txt : CMake project for AGE, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
#using CPM
include(CPM/CPM.cmake)



# https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html
# set C++   standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib )
project ("CPPPathMan")


include_directories("Include/")
file(GLOB_RECURSE  SOURCES "Src/*.cpp")
file(GLOB_RECURSE  INCLUDES "Include/*.hpp")




# Create the source groups for source tree with root at CMAKE_CURRENT_SOURCE_DIR.
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} ${INCLUDES})
add_library(CPP_PATHMAN STATIC ${SOURCES} ${INCLUDES} )

#target_include_directories(CPP_PATHMAN PUBLIC "Include/")




set(CPPPathMan_Test TRUE CACHE BOOL "Enable CPPPathMan Tests" )
 if(${CPPPathMan_Test})
 add_subdirectory(Tests)
 endif()









