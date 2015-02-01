cmake_minimum_required(VERSION 2.8)

project(zmath)

file(GLOB ZMATH_SRCS zmath/*)

if (NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

add_library(zmath STATIC ${ZMATH_SRCS})
