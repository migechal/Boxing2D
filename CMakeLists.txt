
cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(Boxing2D VERSION 2.0.0)

add_executable(${PROJECT_NAME} source/main.cpp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)

find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

target_include_directories(${PROJECT_NAME} PUBLIC header/)

target_link_directories(${PROJECT_NAME} PRIVATE header/)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})

add_subdirectory(source)

target_link_libraries(${PROJECT_NAME} source)
