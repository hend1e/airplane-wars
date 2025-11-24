cmake_minimum_required(VERSION 3.31)
project(airplane_wars)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==== 关键：把项目根目录加入 include 搜索路径 ====
include_directories(${CMAKE_SOURCE_DIR})

# ==== 收集所有 cpp ====
file(GLOB_RECURSE SOURCES
        ${CMAKE_SOURCE_DIR}/arch/*.cpp
        ${CMAKE_SOURCE_DIR}/src/*.cpp
)

add_executable(airplane_wars
        ${SOURCES}
)
