#pragma once
#ifndef _zTools_CRASH_FUNC_H_
#define _zTools_CRASH_FUNC_H_

namespace zTools
{
	class CrashFunc
	{
	public:
		CrashFunc();
		static void CrashFunction(int);

		static const int MAX_JMP_BUF = 16;
		static const int MAX_CALLSTACK_DEPTH = 32;

		enum BufferName
		{
			BufferName_MAIN,
			BufferName_COUNT,
		};
	};
}

#endif