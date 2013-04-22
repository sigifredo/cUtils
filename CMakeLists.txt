project(cUtils)
cmake_minimum_required(VERSION 2.8)

add_executable(md5sum ${CMAKE_SOURCE_DIR}/src/md5sum.cpp)
add_executable(hwaddr ${CMAKE_SOURCE_DIR}/src/hwaddr.c)

target_link_libraries(cpu_info cryptopp)