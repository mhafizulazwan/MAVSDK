cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(subscribe_state)

add_executable(subscribe_state
    subscribe_state.cpp
)

find_package(MAVSDK REQUIRED)

target_link_libraries(subscribe_state
    MAVSDK::mavsdk
)

if(NOT MSVC)
    add_compile_options(subscribe_state PRIVATE -Wall -Wextra)
else()
    add_compile_options(subscribe_state PRIVATE -W2)
endif()
