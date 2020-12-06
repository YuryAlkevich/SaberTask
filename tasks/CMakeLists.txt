cmake_minimum_required(VERSION 3.17)
project(SaberTasks)

set(CMAKE_CXX_STANDARD 11)

add_library(SaberTasks
        Task1.h
        Task2.h
        Task2.cpp
        Task3.h
        Task3.cpp)

target_include_directories(SaberTasks PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
