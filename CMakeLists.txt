cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 11)
project(QuestradeOptionsAPI)

find_package(cpprestsdk REQUIRED)

add_executable(QuestradeOptionsAPI main.cpp access_key.h access_key.cpp)
target_link_libraries(QuestradeOptionsAPI PRIVATE cpprestsdk::cpprest)



