project(game-of-life)
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/CMake)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(SDL2 REQUIRED)

set(INCLUDE_DIR_LIST
    ${SDL2_INCLUDE_DIR}
)

set(LIBRARIES_LIST
    ${SDL2_LIBRARY}
)

set(HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GameOfLifeMap.h
)

set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GameOfLifeMap.cpp
)

include_directories(${INCLUDE_DIR_LIST} ${CMAKE_CURRENT_SOURCE_DIR}/src)
add_executable(gameOfLife ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(gameOfLife ${LIBRARIES_LIST})

