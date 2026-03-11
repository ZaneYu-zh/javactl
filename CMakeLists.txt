cmake_minimum_required(VERSION 3.15)
project(javactl LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(WIN32)
    set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/bin/win-${CMAKE_SYSTEM_PROCESSOR})
elseif(UNIX AND NOT APPLE)
    set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/bin/linux-${CMAKE_SYSTEM_PROCESSOR})
elseif(APPLE)
    set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/bin/mac-${CMAKE_SYSTEM_PROCESSOR})
endif()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OUTPUT_DIR})

if(WIN32)
    set(CURL_ROOT ${CMAKE_SOURCE_DIR}/third_party/curl)
    set(CURL_INCLUDE_DIR ${CURL_ROOT}/include)
    set(CURL_LIBRARY ${CURL_ROOT}/lib/libcurl.a)

    add_library(CURL::libcurl STATIC IMPORTED GLOBAL)
    set_target_properties(CURL::libcurl PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${CURL_INCLUDE_DIR}
        IMPORTED_LOCATION ${CURL_LIBRARY}
    )
    target_compile_definitions(CURL::libcurl INTERFACE CURL_STATICLIB)
else()
    find_package(CURL REQUIRED)
endif()

add_executable(javactl)

file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
target_sources(javactl PRIVATE ${SRC_FILES})

target_include_directories(javactl PRIVATE
    ${CMAKE_SOURCE_DIR}/third_party/json/include
    ${CMAKE_SOURCE_DIR}/include
    $<$<BOOL:${WIN32}>:${CURL_INCLUDE_DIR}>
    $<$<NOT:$<BOOL:${WIN32}>>:${CURL_INCLUDE_DIRS}>
)

target_compile_definitions(javactl PRIVATE
    $<$<BOOL:${WIN32}>:WIN32_LEAN_AND_MEAN>
    $<$<BOOL:${WIN32}>:UNICODE>
    $<$<BOOL:${WIN32}>:_UNICODE>
    $<$<BOOL:${WIN32}>:CURL_STATICLIB>
)

target_link_libraries(javactl PRIVATE
    $<$<BOOL:${WIN32}>:CURL::libcurl>
    $<$<NOT:$<BOOL:${WIN32}>>:CURL::curl>

    $<$<BOOL:${WIN32}>:ws2_32>
    $<$<BOOL:${WIN32}>:wldap32>
    $<$<BOOL:${WIN32}>:winmm>
    $<$<BOOL:${WIN32}>:crypt32>
    $<$<BOOL:${WIN32}>:bcrypt>
    $<$<BOOL:${WIN32}>:iphlpapi>
    $<$<BOOL:${WIN32}>:secur32>
    $<$<BOOL:${WIN32}>:z>

    $<$<AND:$<BOOL:${UNIX}>,$<NOT:$<BOOL:${APPLE}>>>:pthread>
    $<$<AND:$<BOOL:${UNIX}>,$<NOT:$<BOOL:${APPLE}>>>:dl>
    $<$<AND:$<BOOL:${UNIX}>,$<NOT:$<BOOL:${APPLE}>>>:rt>
    $<$<AND:$<BOOL:${UNIX}>,$<NOT:$<BOOL:${APPLE}>>>:z>

    $<$<BOOL:${APPLE}>:CoreFoundation>
    $<$<BOOL:${APPLE}>:SystemConfiguration>
)

if(WIN32)
    target_link_options(javactl PRIVATE
        -static-libgcc
        -static-libstdc++
    )
endif()