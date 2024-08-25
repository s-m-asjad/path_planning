cmake_minimum_required(VERSION 3.15)

project(Globus_Assignment VERSION 1.0)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)
include_directories(jsoncpp)
include_directories(matplotlib_cpp)

add_subdirectory(matplotlib_cpp)
add_subdirectory(jsoncpp)


add_executable(PathPlanning jsoncpp matplotlib_cpp src/main.cpp src/initialization.cpp src/generate_image.cpp src/path_planning.cpp)

target_link_libraries(PathPlanning jsoncpp matplotlib_cpp)