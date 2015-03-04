// PortMonitoring.cpp: implementation of the CPortMonitoring class.
//
//////////////////////////////////////////////////////////////////////
#if defined(_WINDOWS) || defined(WIN32) || defined(_WIN64)

#include "NetworkPortChecker.h"

#define		ANY_SIZE	 120

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
//#define new DEBUG_NEW
#endif

#pragma comment (lib, "Wsock32.lib")
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

using namespace zTools;

//连接信息结构体
typedef struct _MIB_TCPROW
{
	DWORD dwState;							//TCP连接状态
	DWORD dwLocalAddr;						//本地IP
	DWORD dwLocalPort;						//本地端口
	DWORD dwRemoteAddr;						//远程机器IP
	DWORD dwRemotePort;						//远程机器端口
} MIB_TCPROW, *PMIB_TCPROW;

//TCP连接表
typedef struct _MIB_TCPTABLE
{
	DWORD      dwNumEntries;				//当前包含MIB_TCPROW类型的总数
	MIB_TCPROW table[ANY_SIZE];             //存放每个TCP连接的端口和IP
} MIB_TCPTABLE, *PMIB_TCPTABLE;

//UDP绑定信息
typedef struct _MIB_UDPROW {
	DWORD dwLocalAddr;
	DWORD dwLocalPort;
} MIB_UDPROW, *PMIB_UDPROW;

//UDP socket绑定信息表
typedef struct _MIB_UDPTABLE {
	DWORD      dwNumEntries;
	MIB_UDPROW table[ANY_SIZE];
} MIB_UDPTABLE, *PMIB_UDPTABLE;

static const TCHAR* IPHLPAPI_Module_Name = TEXT("iphlpapi.dll");
static const TCHAR* Proc_GetTcpTable_Name = TEXT("GetTcpTable");
static const TCHAR* Proc_GetUdpTable_Name = TEXT("GetUdpTable");

//定义GetTcpTable函数指针类型
typedef int (__stdcall *GetTcpTableProc) (PMIB_TCPTABLE pTcpTable, PDWORD pdwSize, BOOL bOrder);

//定义etUdpTable函数指针类型
typedef int(__stdcall *GetUdpTableProc) (PMIB_UDPTABLE pTcpTable, PDWORD pdwSize, BOOL bOrder);

/*
该模板取巧地使用了MIB_UDPTABLE与MIB_TCPTABLE结构中成员变量table名称相同以及dwLocalPort这个属性的同名的性质
不具有通用性，只在这里可以使用
*/
template<typename ProcType, typename TableType>
NetworkPortChecker::PortCheckerErrNo IsPortValid(UINT nPort, const char* procName)
{
	if (nPort > 65535)
		return NetworkPortChecker::PORTCKERRNO_PARAM_INVALID;

	TableType* ptcptable = NULL;
	DWORD dwSize = 0;

	HINSTANCE hInst;		//动态链接库模块句柄
	hInst = LoadLibrary(IPHLPAPI_Module_Name);		//动态加载iphlpapi.dll
	if (NULL == hInst)
		return NetworkPortChecker::PORTCKERRNO_LOAD_MODULE_FAILED;


	//获取iphlpapi.dll导出函数
	ProcType GetTcpTable = (ProcType)GetProcAddress(hInst, procName);
	if (NULL == GetTcpTable)
		return NetworkPortChecker::PORTCKERRNO_PROC_NOT_FOUND;

	if (GetTcpTable(ptcptable, &dwSize, TRUE) == ERROR_INSUFFICIENT_BUFFER)		//pTcpTable空间不足
	{
		ptcptable = new TableType[dwSize];		//为pTcpTable申请足够的空间

		if (GetTcpTable(ptcptable, &dwSize, TRUE) == NO_ERROR)     //GetTcpTable调用成功
		{
			//检测端口nPort是否在
			for (UINT i = 0; i<ptcptable->dwNumEntries; i++)
			{
				int long_port = ptcptable->table[i].dwLocalPort / 256 + (ptcptable->table[i].dwLocalPort % 256) * 256;
				//printf("TCP - %d\tIP - %d\n", long_port, ptcptable->table[i].dwLocalAddr);
				if (nPort != long_port)
					continue;

				//释放资源
				delete[] ptcptable;
				FreeLibrary((HMODULE)hInst);

				return NetworkPortChecker::PORTCKERRNO_PORT_INVALID;
			}
		}
		else
		{
			//释放资源
			delete[] ptcptable;
			FreeLibrary((HMODULE)hInst);
			return NetworkPortChecker::PORTCKERRNO_PROC_FAILED;//call GetTcpTable failed
		}
	}
	else
	{
		return NetworkPortChecker::PORTCKERRNO_PROC_FAILED;//call GetTcpTable failed
	}
	//释放资源
	delete[] ptcptable;
	FreeLibrary((HMODULE)hInst);

	return NetworkPortChecker::PORTCKERRNO_VALID;
}
//检测端口是否被占用				 
NetworkPortChecker::PortCheckerErrNo NetworkPortChecker::IsPortValid_TCP(UINT nPort)
{
	return IsPortValid<GetTcpTableProc, MIB_TCPTABLE>(nPort, Proc_GetTcpTable_Name);
}

//static 
NetworkPortChecker::PortCheckerErrNo NetworkPortChecker::IsPortValid_UDP(UINT nPort)
{
	return IsPortValid<GetUdpTableProc, MIB_UDPTABLE>(nPort, Proc_GetUdpTable_Name);
}

#endif //#if defined(_WINDOWS) || defined(WIN32) || defined(_WIN64)
