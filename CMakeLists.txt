# 完成对zTools项目的编译

cmake_minimum_required(VERSION 3.1)

project("ztools")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

include_directories(
    "src"
)

set(SrcFiles_Backtrace src/zbacktrace.h src/backtrace.cpp)
set(Lib_Backtrace unwind)

set(source_list 
    ${SrcFiles_Backtrace}
)

link_libraries(
    "${Lib_Backtrace}"
)

# add_library(ztools STATIC ${source_list})
add_library(ztools SHARED ${source_list})