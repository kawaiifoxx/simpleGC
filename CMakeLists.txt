cmake_minimum_required(VERSION 3.17)
project(simpleGC)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES sgc_info.cpp sgc_info.h sgc_iterator.cpp sgc_iterator.h sgc_ptr.cpp sgc_ptr.h)

add_library(simpleGC ${SOURCE_FILES})