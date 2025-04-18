cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(ControlCenter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/ControlCenter/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/ControlCenter/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/ControlCenter/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-static-libstdc++ -static-libgcc")

add_subdirectory(whi3per)
add_executable(${PROJECT_NAME} main.cc)

target_include_directories (
    ${PROJECT_NAME} 
    PUBLIC 
        whi3per/include/public
)

target_link_libraries (
    ${PROJECT_NAME} 
    PUBLIC 
        whi3per
)

target_compile_definitions(${PROJECT_NAME} PRIVATE -D_WIN32_WINNT=0x0501)

find_library(PSAPI_LIBRARY psapi)
if (PSAPI_LIBRARY)
    message(STATUS "Found psapi library: ${PSAPI_LIBRARY}")
else()
    set(PSAPI_LIBRARY "C:/Windows/System32/psapi.dll")
    message(STATUS "Manually set psapi library to: ${PSAPI_LIBRARY}")
endif()

target_link_libraries (
    ${PROJECT_NAME} 
    PUBLIC
        dxgi 
        d3d11
        psapi
        ole32 
        user32 
        gdi32 
        Dxva2
        kernel32
        ws2_32
        iphlpapi
)
