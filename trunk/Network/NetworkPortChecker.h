// NetworkPortChecker.h: interface for the NetworkPortChecker class.
// 检查TCP、UDP端口是否可用（即可以绑定），一般认为已被占用的端口则不再可用（此处没有考虑端口的Reuse）
// 使用iphlpapi.dll库中的GetTCPTable、GetUdpTable来实现获取系统中已经被占用的端口
// 只判断IPv4的端口，暂不支持IPv6的端口
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

/*网络端口是否空闲的检测类，只封装了检测的静态方法，无成员变量*/
class NetworkPortChecker  
{
public:
	/*返回码的枚举*/
	enum PortCheckerErrNo
	{
		PORTCKERRNO_VALID				= 0,		//端口空闲
		PORTCKERRNO_PORT_INVALID		= 1,		//端口已被占用
		PORTCKERRNO_PARAM_INVALID		= 2,		//非法参数
		PORTCKERRNO_LOAD_MODULE_FAILED	= 3,		//加载iphlpapi.dll失败
		PORTCKERRNO_PROC_NOT_FOUND		= 4,		//无法查找到GetTcpTable或者GetUdpTable方法
		PORTCKERRNO_PROC_FAILED			= 5,		//GetTcpTable或者GetUdpTable方法执行失败
	};

	/**
	 *	@name		IsPortValid_TCP
	 *	@brief		检测TCP端口是否空闲
	 *	@param[in]	UINT nPort	检查的TCP端口
	 *	@return		0--端口空闲 1--端口被占用 其他--方法调用失败，此时无法判断端口是否空闲
	 **/
	static PortCheckerErrNo IsPortValid_TCP(UINT nPort);

	/**
	*	@name		IsPortValid_UDP
	*	@brief		检测UDP端口是否空闲
	*	@param[in]	UINT nPort	检查的UDP端口
	*	@return		PortCheckerErrNo 0--端口空闲 1--端口被占用 其他--方法调用失败，此时无法判断端口是否空闲
	**/
	static PortCheckerErrNo IsPortValid_UDP(UINT nPort);
};
}//namespace zTools

#endif // !defined(AFX_PORTMONITORING_H__A8CBE1A3_0489_4DA0_862F_F3CDFFE4AB9C__INCLUDED_)
#endif // #if defined(_WINDOWS) || defined(WIN32) || defined(_WIN64)