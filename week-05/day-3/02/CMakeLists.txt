cmake_minimum_required(VERSION 3.13)
project(02)

set(CMAKE_CXX_STANDARD 14)

add_executable(02 main.cpp Employees.cpp Employees.h Waiter.cpp Waiter.h Chef.cpp Chef.h)