/*
 *	@file		BroadcastSocket.h
 *	@data		2012-12-5 10:35
 *	@author		zhu qing quan
 *	@brief		�㲥��Ϣ���ͺͽ��յ�SOCKET
 *  @Copyright	(C) 2012, by Ragile Corporation
 */

#pragma once
#ifndef _BROADCAST_SOCKET_H_
#define _BROADCAST_SOCKET_H_

#include <string>
#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

namespace SOA
{
namespace Mirror
{
namespace RPC
{
	/**
	 * @name	BroadcastSocket
	 * @brief	�㲥��Ϣ���ͺͽ��յ�SOCKET
	 */
	class BroadcastSocket
	{
	public:
		/**
		 * Method		BroadcastSocket
		 * @brief		�㲥��Ϣ��SOCKET����ʵ�����鲥ʵ��
		 * @param[in]	const std::string & multicastIP �鲥��IP
		 * @param[in]	int port �鲥�˿�
		 */
		BroadcastSocket(const std::string& multicastIP, int port);
		/**
		 * Method		~BroadcastSocket
		 * @brief		�����������ͷ���Դ
		 */
		~BroadcastSocket();

		/**
		 * Method		send
		 * @brief		������Ϣ���鲥��ַ��
		 * @param[in]	const char * msg ��Ϣ��
		 * @param[in]	int offset ƫ����
		 * @param[in]	int length ���͵ĳ���
		 * @return		int ����ʵ���ѷ��͵����ݳ��ȣ�-1Ϊʧ��
		 */
		int send(const char* msg, int offset, int length);

		/**
		 * Method		recv
		 * @brief		���鲥��ַ�н�������
		 * @param[in]	char * msgBuffer ��Ž��յ������ݵ��ڴ��
		 * @param[in]	int offset ���ݴ�ŵ�ƫ����
		 * @param[in]	int length ���ó���
		 * @return		int ʵ�ʽ��յ������ݵĳ��ȣ� -1Ϊʧ��
		 */
		int recv(char* msgBuffer, int offset, int length);

	private:
		SOCKET m_sendSocket;
		SOCKET m_recvSocket;
		sockaddr_in m_multicastAddr;
		struct ip_mreq m_mreq;
	};
}
}
}

#endif