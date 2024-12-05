cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(trigger_micasense)

find_package(CURL REQUIRED)

add_executable(trigger_micasense
    trigger_micasense.cpp
    micasense.cpp
    cloud.cpp
)

find_package(MAVSDK REQUIRED)

target_link_libraries(trigger_micasense
    MAVSDK::mavsdk
    CURL::libcurl
)

if(NOT MSVC)
    add_compile_options(trigger_micasense PRIVATE -Wall -Wextra)
else()
    add_compile_options(trigger_micasense PRIVATE -W2)
endif()
