cmake_minimum_required(VERSION 3.17)
project(Tests)

include(FetchContent)

FetchContent_Declare(
        gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.8.0
)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING")
endif ()
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(gtest)

add_executable(Tests
        tests.cpp)

target_link_libraries(Tests
        SaberTasks
        gtest
        gtest_main)

add_test(NAME SaberTaskTests COMMAND Tests)
