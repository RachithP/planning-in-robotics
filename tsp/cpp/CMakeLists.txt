project (cpp)

cmake_minimum_required (VERSION 3.5)
add_definitions(-std=c++11)

set(CXX_FLAGS "-Wall -pthread")
set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")

find_package( OpenCV REQUIRED )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
#include_directories(/usr/local/include)
#link_directories(/usr/local/lib)

add_executable(hw1_executable src/main.cpp src/vertex.cpp src/edge.cpp src/costmap.cpp src/minheap.cpp)
target_link_libraries( hw1_executable ${OpenCV_LIBS} )
