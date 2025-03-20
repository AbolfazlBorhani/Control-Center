cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(ControlCenter LANGUAGES CXX)

add_subdirectory(whi3perlib)
add_executable(${PROJECT_NAME} main.cc)

target_include_directories (
    ${PROJECT_NAME} 
    PUBLIC 
        whi3perlib/include/public
)

target_link_libraries (
    ${PROJECT_NAME} 
    PUBLIC 
        whi3perlib
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