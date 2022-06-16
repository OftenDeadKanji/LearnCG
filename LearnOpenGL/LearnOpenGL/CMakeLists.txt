cmake_minimum_required(VERSION 3.18)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 20)

add_executable(LearnOpenGL "")
add_subdirectory(src)
add_subdirectory("dependencies/Glad/")
add_subdirectory("dependencies/imgui/")

set_property(TARGET LearnOpenGL PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}") 

#includes
target_include_directories(LearnOpenGL PRIVATE "dependencies/include/")
target_include_directories(LearnOpenGL PRIVATE "dependencies/imgui")

#libraries
find_package(OpenGL REQUIRED)

set(LIB_PATH "${PROJECT_SOURCE_DIR}/dependencies/lib/")

if(MSVC)
	string(APPEND LIB_PATH "msvc/")
else()
	message(FATAL_ERROR "Unsupported compiler!")
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
	string(APPEND LIB_PATH "debug/")
else()
	string(APPEND LIB_PATH "release/")
endif()

find_library(LIB_GLFW NAMES glfw glfw3 PATHS ${LIB_PATH} REQUIRED)
find_library(LIB_BOOST_FILESYSTEM NAMES libboost_filesystem PATHS ${LIB_PATH} REQUIRED)
find_library(LIB_ZLIB NAMES zlibstatic PATHS ${LIB_PATH} REQUIRED)
find_library(LIB_ASSIMP NAMES assimp PATHS ${LIB_PATH} REQUIRED)

#message(LIB_BOOST_FILESYSTEM)

target_link_libraries(LearnOpenGL PRIVATE opengl32 ${LIB_GLFW} ${LIB_BOOST_FILESYSTEM} ${LIB_GLFW} ${LIB_ZLIB} ${LIB_ASSIMP})