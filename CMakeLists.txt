cmake_minimum_required(VERSION 3.16)
project(pfs VERSION 0.0.1)
set (CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} pfs.cpp)

# adding the file-system dir
add_subdirectory(file-system)
target_link_libraries(${PROJECT_NAME} PRIVATE fs)