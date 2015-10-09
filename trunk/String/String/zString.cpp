#include "zString.h"

#include <fstream>

using namespace zTools;

int zTools::get_line(std::istream& inputStr, char* lineStr, int& lineStrSize)
{
	if(!inputStr)
	{
		lineStrSize = 0;
		return 0;
	}
	char c = '\n';
	int linePos = 0;
	while(linePos<lineStrSize && !inputStr.get(c).eof() /*&& c!='\n'*/)
	{
		if(c=='\r')
		{
			char t = inputStr.peek();
			if(t=='\n')
				inputStr.get(c);
			else
				c = '\n';
		}
		lineStr[linePos] = c;
		linePos++;
	}
	std::istream::pos_type before = inputStr.tellg();
	inputStr.getline(lineStr, lineStrSize);
	lineStrSize = strlen(lineStr);
	std::istream::pos_type after = inputStr.tellg();
	return after - before;
}

int main(int argc, char* argv[])
{
	std::ifstream inputFileStream("a.txt", std::ios::in);
	char line[1024] = {0};
	int lineSize = 1024;
	while(0<get_line(inputFileStream, line, lineSize))
	{
		printf("> %s", line);
	}
	getchar();
	return 0;
}