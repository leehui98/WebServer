cmake_minimum_required(VERSION 3.16)
project(myWebserver)
file(GLOB SRC "*.cpp")
set(CXX_FLAGS -std=c++11)
add_executable(myWebserver ${SRC})
target_link_libraries(myWebserver 
-lpthread
)
