# 完成对zTools项目中代码测试用例的编译

cmake_minimum_required(VERSION 3.1)

project("ztools_test")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")


include_directories(
    "."
    "../src"
)

link_directories(
    "../build"
)

# set(SrcFiles_Backtrace src/backtrace.h src/backtrace.cpp)
# set(Lib_Backtrace unwind)

#set(source_list 
#    ${SrcFiles_Backtrace}
#)
#
link_libraries(
    "${Lib_Backtrace}" 
    ztools
)

# add_library(ztools STATIC ${source_list})
add_executable(test_backtrace main_backtrace.cpp)