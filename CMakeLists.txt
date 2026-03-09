cmake_minimum_required(VERSION 3.15)
project(javactl)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/third_party/json/include)

find_package(CURL REQUIRED)

add_executable(javactl src/main.cpp)

target_include_directories(javactl PRIVATE include)
target_link_libraries(javactl PRIVATE CURL::libcurl)