
cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(Boxing2D VERSION 2.0.0)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} source/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC header/)

target_link_directories(${PROJECT_NAME} PRIVATE header/)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

add_subdirectory(source)

target_link_libraries(${PROJECT_NAME} source)
