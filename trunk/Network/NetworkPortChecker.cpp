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

//������Ϣ�ṹ��
typedef struct _MIB_TCPROW
{
	DWORD dwState;							//TCP����״̬
	DWORD dwLocalAddr;						//����IP
	DWORD dwLocalPort;						//���ض˿�
	DWORD dwRemoteAddr;						//Զ�̻���IP
	DWORD dwRemotePort;						//Զ�̻����˿�
} MIB_TCPROW, *PMIB_TCPROW;

//TCP���ӱ�
typedef struct _MIB_TCPTABLE
{
	DWORD      dwNumEntries;				//��ǰ����MIB_TCPROW���͵�����
	MIB_TCPROW table[ANY_SIZE];             //���ÿ��TCP���ӵĶ˿ں�IP
} MIB_TCPTABLE, *PMIB_TCPTABLE;

//UDP����Ϣ
typedef struct _MIB_UDPROW {
	DWORD dwLocalAddr;
	DWORD dwLocalPort;
} MIB_UDPROW, *PMIB_UDPROW;

//UDP socket����Ϣ��
typedef struct _MIB_UDPTABLE {
	DWORD      dwNumEntries;
	MIB_UDPROW table[ANY_SIZE];
} MIB_UDPTABLE, *PMIB_UDPTABLE;

static const TCHAR* IPHLPAPI_Module_Name = TEXT("iphlpapi.dll");
static const TCHAR* Proc_GetTcpTable_Name = TEXT("GetTcpTable");
static const TCHAR* Proc_GetUdpTable_Name = TEXT("GetUdpTable");

//����GetTcpTable����ָ������
typedef int (__stdcall *GetTcpTableProc) (PMIB_TCPTABLE pTcpTable, PDWORD pdwSize, BOOL bOrder);

//����etUdpTable����ָ������
typedef int(__stdcall *GetUdpTableProc) (PMIB_UDPTABLE pTcpTable, PDWORD pdwSize, BOOL bOrder);

/*
��ģ��ȡ�ɵ�ʹ����MIB_UDPTABLE��MIB_TCPTABLE�ṹ�г�Ա����table������ͬ�Լ�dwLocalPort������Ե�ͬ��������
������ͨ���ԣ�ֻ���������ʹ��
*/
template<typename ProcType, typename TableType>
NetworkPortChecker::PortCheckerErrNo IsPortValid(UINT nPort, const char* procName)
{
	if (nPort > 65535)
		return NetworkPortChecker::PORTCKERRNO_PARAM_INVALID;

	TableType* ptcptable = NULL;
	DWORD dwSize = 0;

	HINSTANCE hInst;		//��̬���ӿ�ģ����
	hInst = LoadLibrary(IPHLPAPI_Module_Name);		//��̬����iphlpapi.dll
	if (NULL == hInst)
		return NetworkPortChecker::PORTCKERRNO_LOAD_MODULE_FAILED;


	//��ȡiphlpapi.dll��������
	ProcType GetTcpTable = (ProcType)GetProcAddress(hInst, procName);
	if (NULL == GetTcpTable)
		return NetworkPortChecker::PORTCKERRNO_PROC_NOT_FOUND;

	if (GetTcpTable(ptcptable, &dwSize, TRUE) == ERROR_INSUFFICIENT_BUFFER)		//pTcpTable�ռ䲻��
	{
		ptcptable = new TableType[dwSize];		//ΪpTcpTable�����㹻�Ŀռ�

		if (GetTcpTable(ptcptable, &dwSize, TRUE) == NO_ERROR)     //GetTcpTable���óɹ�
		{
			//���˿�nPort�Ƿ���
			for (UINT i = 0; i<ptcptable->dwNumEntries; i++)
			{
				int long_port = ptcptable->table[i].dwLocalPort / 256 + (ptcptable->table[i].dwLocalPort % 256) * 256;
				//printf("TCP - %d\tIP - %d\n", long_port, ptcptable->table[i].dwLocalAddr);
				if (nPort != long_port)
					continue;

				//�ͷ���Դ
				delete[] ptcptable;
				FreeLibrary((HMODULE)hInst);

				return NetworkPortChecker::PORTCKERRNO_PORT_INVALID;
			}
		}
		else
		{
			//�ͷ���Դ
			delete[] ptcptable;
			FreeLibrary((HMODULE)hInst);
			return NetworkPortChecker::PORTCKERRNO_PROC_FAILED;//call GetTcpTable failed
		}
	}
	else
	{
		return NetworkPortChecker::PORTCKERRNO_PROC_FAILED;//call GetTcpTable failed
	}
	//�ͷ���Դ
	delete[] ptcptable;
	FreeLibrary((HMODULE)hInst);

	return NetworkPortChecker::PORTCKERRNO_VALID;
}
//���˿��Ƿ�ռ��				 
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
