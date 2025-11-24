cmake_minimum_required(VERSION 3.31)
project(airplane_wars)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 让 include "arch/xxx.h" 生效
include_directories(${CMAKE_SOURCE_DIR})

# 只编译 src/ 下的 .cpp，不要碰 arch/
file(GLOB_RECURSE SOURCES
        ${CMAKE_SOURCE_DIR}/src/*.cpp
)

add_executable(airplane_wars
        ${SOURCES}
        src/behavior/EnemyBehavior.cpp
        src/behavior/BulletBehavior.cpp
        src/behavior/PlayerBehavior.cpp
        src/behavior/PropBehavior.cpp
)
