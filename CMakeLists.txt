cmake_minimum_required(VERSION 2.8)
project (mq)

include_directories (
    "include"
    )

add_executable (mq
    src/mq.cpp
    )

target_link_libraries( 
    mq
    -pthread
    )

set_target_properties (mq
    PROPERTIES
    COMPILE_FLAGS
    "${CMAKE_CXX_FLAGS} -std=c++11"
    )
