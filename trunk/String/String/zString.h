/**
 * @file 	zString.h
 * @brief 	Some function to operate String, like getLine, match... etc.
 * @author 	zhuqingquan
 * @version 1.0.0.0
 * @data 	2014/12/14   11:07
 **/

#pragma once
#ifndef _ZTOOLS_STRING_ZSTRING_H_
#define _ZTOOLS_STRING_ZSTRING_H_

#include <istream>

namespace zTools
{
	/**
	 *	@name		get_line
	 *	@brief		从字符流中读取一行，以'\n'或者'\r'或者'\r\n'作为一行的分割符。如果整个字符流读取到了最后还是没有遇到'\n'则已经读取的所有字符作为一行以'\0'结束
	 *				读取的数据以'\0'结束，'\n'字符不保存在结果中
	 *	@param[in]	std::istream& inputStr 输入的字符流，从该字符流读取数据，读取出来的数据不再存在于该字符流中
	 *	@param[out]	char* lineStr 保存读取到的一行字符的字符串空间，其初始化长度由lineStrSize参数指定
	 *	@param[in,out]	int& lineStrSize 传入lineStr字符串空间初始化长度，传出读取到的一行字符串的实际长度
	 *	@return		返回已经从字符流中读取了多少个字符。如果刚好读取的字符串是以'\r\n'作为行结束符，则可能lineStrSize的值不等于return返回的值。
	 **/
	int get_line(std::istream& inputStr, char* lineStr, int& lineStrSize);

	int get_line(FILE* hFile, char* lineStr, int& lineStrSize);
	int get_line(int socket, char* lineStr, int& lineStrSize);
	//int get_line(std::string& socket, char* lineStr, int& lineStrSize);

	template<typename InputStreamType>
	int getLine(InputStreamType inputStr, char* lineStr, int& lineStrSize)
	{
		return get_line<InputStreamType>(inputStr, lineStr, lineStrSize);
	};
}

#endif //_ZTOOLS_STRING_ZSTRING_H_