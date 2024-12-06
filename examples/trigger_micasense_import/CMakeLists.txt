cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(trigger_micasense_import)

find_package(CURL REQUIRED)

add_executable(trigger_micasense_import
    trigger_micasense_import.cpp
    micasense.cpp
    cloud.cpp
)

find_package(MAVSDK REQUIRED)

target_link_libraries(trigger_micasense_import
    MAVSDK::mavsdk
    CURL::libcurl
)

if(NOT MSVC)
    add_compile_options(trigger_micasense_import PRIVATE -Wall -Wextra)
else()
    add_compile_options(trigger_micasense_import PRIVATE -W2)
endif()
