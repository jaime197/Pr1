cmake_minimum_required(VERSION 3.5)

set(CMAKE_BUILD_TYPE Debug)

project(server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


project(client LANGUAGES CXX)
add_executable(client utils.h utils.cpp client.cpp multmatrix_stub.cpp)
target_link_libraries(client pthread)