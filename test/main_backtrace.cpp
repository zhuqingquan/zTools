/*
 * @Author: your name
 * @Date: 2021-05-28 00:34:59
 * @LastEditTime: 2021-05-30 17:33:50
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /backtrace/main.cpp
 */
#include <stdio.h>
#include "zbacktrace.h"

void foo()
{
    std::string strbt = z_backtrace();
    printf("%s\n", strbt.c_str());
}

void bar()
{
    foo();
}

int main(int argc, char* argv[])
{
    printf("backtrace start.\n");

    bar();
    return 0;
}