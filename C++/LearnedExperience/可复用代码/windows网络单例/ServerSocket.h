﻿#pragma once

#include "pch.h"
#include "framework.h"

class CServerSocket
{
public:
	static CServerSocket* getInstance() {
		if(m_instance == NULL)
			m_instance = new CServerSocket();
		return m_instance;
	}
	bool InitSocket() {
		
		sockaddr_in serv_adr;
		memset(&serv_adr, 0, sizeof(serv_adr));
		serv_adr.sin_family = AF_INET;
		serv_adr.sin_addr.s_addr = INADDR_ANY;
		serv_adr.sin_port = htons(8001);

		if (bind(m_sock, (sockaddr*)&serv_adr, sizeof(serv_adr)) == -1) {
			return false;
		}
		
		if (listen(m_sock, 1) == -1) {
			return false;
		}

		return true;
		/*sockaddr_in client_adr;
		int client_size;
		SOCKET client_sock = accept(serv_sock, (sockaddr*)&client_adr, &client_size);

		char buffer[1024];
		recv(client_sock, buffer, sizeof(buffer), 0);
		send(client_sock, buffer, strlen(buffer), 0);
		closesocket(client_sock);
		closesocket(serv_sock);*/
	}

	bool AcceptClient() {
		sockaddr_in client_adr;
		int client_size;
		m_client = accept(m_sock, (sockaddr*)&client_adr, &client_size);
		if (m_client == -1) {
			return false;
		}
		return true;
		//char buffer[1024];
		//recv(client_sock, buffer, sizeof(buffer), 0);
		//send(client_sock, buffer, strlen(buffer), 0);
		//closesocket(client_sock);
		
	}

	int DealCommand() {
		if (m_client == -1) return 0;

		char buffer[1024];
		while (true) {
			int len = recv(m_client, buffer, sizeof(buffer), 0);
			if (len <= 0) {
				return -1;
			}
			//TODO:处理命令
		}
	}

	bool Send(const char* pData, int nSize) {
		if (m_client == -1) return false;
		return send(m_client, pData, nSize, 0) > 0;
	}
private: 
	SOCKET m_sock;
	SOCKET m_client;
	CServerSocket& operator=(const CServerSocket& ss){
		m_sock = ss.m_sock;
		m_client = ss.m_client;
	}
	CServerSocket(const CServerSocket& ss) {
		m_sock = ss.m_sock;
		m_client = ss.m_client;
	}
	CServerSocket(){
		m_client = INVALID_SOCKET;
		if (InitSockEnv() == FALSE) {
			MessageBox(NULL, _T("无法初始化套接字环境，请检查网络设置"), _T("初始化错误"),MB_OK | MB_ICONERROR);
			exit(0);
		}
		m_sock = socket(PF_INET, SOCK_STREAM, 0);
		if (m_sock == -1) {
			MessageBox(NULL, _T("无法初始化套接字，请检查网络设置"), _T("初始化错误"), MB_OK | MB_ICONERROR);
			exit(0);
		}
	}
	~CServerSocket(){
		closesocket(m_sock);
		WSACleanup();
	}

	BOOL InitSockEnv() {
		WSADATA data;
		if (WSAStartup(MAKEWORD(1, 1), &data) != 0) {
			return FALSE;
		}
		return TRUE;
	}
	static void releaseInstance() {
		if (m_instance != NULL) {
			CServerSocket* temp = m_instance;
			m_instance = NULL;
			delete temp;
		}
	}
	static CServerSocket* m_instance;

	class CHelper {
	public:
		CHelper() {
			CServerSocket::getInstance();
		}
		~CHelper() {
			CServerSocket::releaseInstance();                                     
		}
	};
	static CHelper m_helper;
};


//extern CServerSocket server;