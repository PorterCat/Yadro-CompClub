cmake_minimum_required(VERSION 3.15)
project(compclub LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCES
    ${SRC_DIR}/*.cpp
    ${SRC_DIR}/*.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${SRC_DIR}     
    ${SRC_DIR}/shared 
    ${SRC_DIR}/events
    ${SRC_DIR}/parser
)