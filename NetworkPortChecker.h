// NetworkPortChecker.h: interface for the NetworkPortChecker class.
// ���TCP��UDP�˿��Ƿ���ã������԰󶨣���һ����Ϊ�ѱ�ռ�õĶ˿����ٿ��ã��˴�û�п��Ƕ˿ڵ�Reuse��
// ʹ��iphlpapi.dll���е�GetTCPTable��GetUdpTable��ʵ�ֻ�ȡϵͳ���Ѿ���ռ�õĶ˿�
// ֻ�ж�IPv4�Ķ˿ڣ��ݲ�֧��IPv6�Ķ˿�
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETWORKPORTCHECKER_H__A8CBE1A3_0489_4DA0_862F_F3CDFFE4AB9C__INCLUDED_)
#define AFX_NETWORKPORTCHECKER_H__A8CBE1A3_0489_4DA0_862F_F3CDFFE4AB9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if defined(_WINDOWS) || defined(WIN32) || defined(_WIN64)

#include <Windows.h>
namespace zTools
{

/*����˿��Ƿ���еļ���ֻ࣬��װ�˼��ľ�̬�������޳�Ա����*/
class NetworkPortChecker  
{
public:
	/*�������ö��*/
	enum PortCheckerErrNo
	{
		PORTCKERRNO_VALID				= 0,		//�˿ڿ���
		PORTCKERRNO_PORT_INVALID		= 1,		//�˿��ѱ�ռ��
		PORTCKERRNO_PARAM_INVALID		= 2,		//�Ƿ�����
		PORTCKERRNO_LOAD_MODULE_FAILED	= 3,		//����iphlpapi.dllʧ��
		PORTCKERRNO_PROC_NOT_FOUND		= 4,		//�޷����ҵ�GetTcpTable����GetUdpTable����
		PORTCKERRNO_PROC_FAILED			= 5,		//GetTcpTable����GetUdpTable����ִ��ʧ��
	};

	/**
	 *	@name		IsPortValid_TCP
	 *	@brief		���TCP�˿��Ƿ����
	 *	@param[in]	UINT nPort	����TCP�˿�
	 *	@return		0--�˿ڿ��� 1--�˿ڱ�ռ�� ����--��������ʧ�ܣ���ʱ�޷��ж϶˿��Ƿ����
	 **/
	static PortCheckerErrNo IsPortValid_TCP(UINT nPort);

	/**
	*	@name		IsPortValid_UDP
	*	@brief		���UDP�˿��Ƿ����
	*	@param[in]	UINT nPort	����UDP�˿�
	*	@return		PortCheckerErrNo 0--�˿ڿ��� 1--�˿ڱ�ռ�� ����--��������ʧ�ܣ���ʱ�޷��ж϶˿��Ƿ����
	**/
	static PortCheckerErrNo IsPortValid_UDP(UINT nPort);
};
}//namespace zTools

#endif // !defined(AFX_PORTMONITORING_H__A8CBE1A3_0489_4DA0_862F_F3CDFFE4AB9C__INCLUDED_)
#endif // #if defined(_WINDOWS) || defined(WIN32) || defined(_WIN64)