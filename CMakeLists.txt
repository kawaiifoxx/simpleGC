cmake_minimum_required(VERSION 3.17)
project(simpleGC)

set(CMAKE_CXX_STANDARD 14)
set(PREFIX ./src)
set(SOURCE_FILES ${PREFIX}/sgc_info.cpp ${PREFIX}/sgc_info.h ${PREFIX}/sgc_iterator.cpp
        ${PREFIX}/sgc_iterator.h ${PREFIX}/sgc_ptr.cpp ${PREFIX}/sgc_ptr.h)

add_library(simpleGC ${SOURCE_FILES})