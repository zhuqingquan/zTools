/*
 * @Author: zqq
 * @Description: Simple implementaion to get current backtrace
 * implete base on lib unwind
 * @FilePath: /zTools/src/backtrace.cpp
 */
#define UNW_LOCAL_ONLY
#include <libunwind.h>
#include <cxxabi.h>
#include "zbacktrace.h"

std::string z_backtrace()
{
    std::string result;
#ifdef WINDOWS
    const char* newline = "\r\n";
#else
    const char* newline = "\n";
#endif
    unw_cursor_t cursor;
    unw_context_t context;

    unw_getcontext(&context);
    unw_init_local(&cursor, &context);

    char tmpMsg[512] = {0};
    char strIpAddr[100] = {0};
    while(unw_step(&cursor)>0)
    {
        unw_word_t offset, pc;
        unw_get_reg(&cursor, UNW_REG_IP, &pc);
        if(pc==0)
        {
            break;
        }
        //此地址为调用backtrace()后的第一条指令的地址，可以使用addr2line 0x400968 -e main 打印出文件名与行数
        //也可以使用pyelftools中的dwarf_decode_address
        sprintf(strIpAddr, "0x%lx:", pc);

        char sym[256] = {0};
        if(unw_get_proc_name(&cursor, sym, sizeof(sym), &offset)==0)
        {
            char* name = sym;
            int status = -1;
            char* demangled = abi::__cxa_demangle(sym, nullptr, nullptr, &status);
            if(0==status)
            {
                name = demangled;
            }
            sprintf(tmpMsg, "%s (%s+0x%lx)%s", strIpAddr, name, offset, newline);
        }
        else
        {
            printf("error: unable to obtain symbol name for this frame\n");
        }
        result.append(tmpMsg);
    }
    return result;
}