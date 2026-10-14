cmake_minimum_required(VERSION 3.20)

project(jjsasm VERSION 0.01 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(jjsasm
    src/main.c
    src/vector.c
    src/jjsasm.c
)

target_include_directories(jjsasm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)