project(cUtils)
cmake_minimum_required(VERSION 2.8)

add_executable(md5sum ${CMAKE_SOURCE_DIR}/src/md5sum.cpp)
add_executable(hwaddr ${CMAKE_SOURCE_DIR}/src/hwaddr.c)
add_executable(driver_lsusb ${CMAKE_SOURCE_DIR}/src/driver_lsusb.c)

target_link_libraries(md5sum cryptopp)
target_link_libraries(driver_lsusb usb-1.0)
