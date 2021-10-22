cmake_minimum_required(VERSION 3.16)
project(pfs VERSION 0.0.1)
set (CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} pfs.cpp)

# adding the block-device dir
add_subdirectory(block-device)
target_link_libraries(${PROJECT_NAME} PRIVATE blkd)