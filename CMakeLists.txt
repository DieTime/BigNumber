cmake_minimum_required(VERSION 3.15)
project(BIGINT)

set(CMAKE_CXX_STANDARD 14)

add_executable(BIGINT main.cpp BigInt/BigInt.cpp BigInt/BigInt.h)