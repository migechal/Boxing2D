cmake_minimum_required(VERSION 3.19)
project(Boxing2D_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Boxing2D_2
        source/Game.cpp source/main.cpp source/Player.cpp include/Player.h source/WindowManager.cpp include/WindowManager.h source/Types.cpp include/Types.h)
