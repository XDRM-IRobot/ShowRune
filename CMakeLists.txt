cmake_minimum_required (VERSION 2.8)

project (RuneDis)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")

add_executable(RuneDis myrune.cpp)

find_package( OpenCV REQUIRED )
include_directories ( 
    /usr/local/include
    /usr/include 
${OpenCV_INCLUDE_DIRS})

target_link_libraries(RuneDis ${OpenCV_LIBS}
    )
