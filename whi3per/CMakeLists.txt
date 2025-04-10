cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(whi3per LANGUAGES CXX)

include(cmake_utility/organize_source_files.cmake)

add_library (
    ${PROJECT_NAME}
    ${source_files}
    ${private_header_files}
    ${public_header_files}
)

target_include_directories (
    ${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/private
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/public
)

target_compile_definitions(${PROJECT_NAME} PRIVATE -D_WIN32_WINNT=0x0501)