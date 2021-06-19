cmake_minimum_required(VERSION 3.7)

set(CMAKE_C_COMPILER "/usr/bin/gcc")

project(Boxing2D)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-lstdc++fs")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(${PROJECT_NAME} source/main.cpp)
# 
target_link_directories(${PROJECT_NAME} PUBLIC header/)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2 ${SDL2_IMAGE_LIBRARIES})


add_subdirectory(source)
target_link_libraries(${PROJECT_NAME} PUBLIC source)
