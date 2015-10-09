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
	 *	@brief		���ַ����ж�ȡһ�У���'\n'����'\r'����'\r\n'��Ϊһ�еķָ������������ַ�����ȡ���������û������'\n'���Ѿ���ȡ�������ַ���Ϊһ����'\0'����
	 *				��ȡ��������'\0'������'\n'�ַ��������ڽ����
	 *	@param[in]	std::istream& inputStr ������ַ������Ӹ��ַ�����ȡ���ݣ���ȡ���������ݲ��ٴ����ڸ��ַ�����
	 *	@param[out]	char* lineStr �����ȡ����һ���ַ����ַ����ռ䣬���ʼ��������lineStrSize����ָ��
	 *	@param[in,out]	int& lineStrSize ����lineStr�ַ����ռ��ʼ�����ȣ�������ȡ����һ���ַ�����ʵ�ʳ���
	 *	@return		�����Ѿ����ַ����ж�ȡ�˶��ٸ��ַ�������պö�ȡ���ַ�������'\r\n'��Ϊ�н������������lineStrSize��ֵ������return���ص�ֵ��
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