# CMakeList.txt : CMake project for AGE, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project ("CPPPathManTesting")
CPMAddPackage("gh:catchorg/Catch2@3.1.0") 
include_directories("Include/")
file(GLOB_RECURSE  SOURCES "Src/*.cpp")
file(GLOB_RECURSE  INCLUDES "Include/*.hpp")

# Create the source groups for source tree with root at CMAKE_CURRENT_SOURCE_DIR.
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES} ${INCLUDES})
add_executable(CPPPathManTesting ${SOURCES} ${INCLUDES} )
target_link_libraries(CPPPathManTesting CPP_PATHMAN Catch2WithMain)
#target_include_directories(CPPPathManTesting PUBLIC "Include/")




  


