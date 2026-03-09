cmake_minimum_required(VERSION 3.15)
project(javactl LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set(CURL_ROOT ${CMAKE_SOURCE_DIR}/third_party/curl)
set(CURL_INCLUDE_DIR ${CURL_ROOT}/include)
set(CURL_LIBRARY ${CURL_ROOT}/lib/libcurl.a)

add_library(CURL::libcurl STATIC IMPORTED GLOBAL)

set_target_properties(CURL::libcurl PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ${CURL_INCLUDE_DIR}
    IMPORTED_LOCATION ${CURL_LIBRARY}
)

target_compile_definitions(CURL::libcurl INTERFACE CURL_STATICLIB)

include_directories(
    ${CMAKE_SOURCE_DIR}/third_party/json/include
    ${CMAKE_SOURCE_DIR}/include
)

file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(javactl ${SRC_FILES})

target_link_libraries(javactl PRIVATE
    CURL::libcurl
    ws2_32
    wldap32
    winmm
    crypt32
    z
    bcrypt
    iphlpapi
    secur32
    -static-libgcc -static-libstdc++
)

if(WIN32)
    target_compile_definitions(javactl PRIVATE
        WIN32_LEAN_AND_MEAN
        UNICODE
        _UNICODE
    )
endif()