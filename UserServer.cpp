// UserServer.cpp: implementation of the UserServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FeiQ.h"
#include "UserServer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

UserServer::UserServer()
{
	m_pUserView = NULL;
	m_pChatView = NULL;
}

UserServer::~UserServer()
{

}
BOOL UserServer::InitServer()
{
	//����UDP������
	m_svrSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	//�󶨶˿ں�IP
	struct sockaddr_in addr = {0};
	addr.sin_family				= AF_INET;
	addr.sin_port				= htons(PORT_USERSVR);
	addr.sin_addr.S_un.S_addr	= htonl(INADDR_ANY);
	bind(m_svrSocket,(struct sockaddr*)&addr, sizeof(addr));

	//�����������߳�

	AfxBeginThread(UserThread, this);

	return TRUE;
}

//�������ݵ��߳�
UINT UserServer::UserThread(LPVOID pParam)
{

	UserServer* pThis = (UserServer*)pParam;
	//���ܿͻ��˵����ݣ�UDP��
	while (1)
	{
		UDPPACKET packet = {0};
		struct sockaddr_in addr = { 0 };
		int nLen = sizeof(addr);

		if (SOCKET_ERROR == recvfrom(pThis->m_svrSocket, (char*)&packet, sizeof(packet),
														0,(struct sockaddr*)&addr,&nLen))
		{
			AfxMessageBox(_T("AAA"));
		}
		char* pszIP = inet_ntoa(addr.sin_addr);
		switch(packet.header.nCmdID) 
		{
		case NETCMDID_USERBROADCAST:
			pThis->OnUserBroadcast((LPUSERBROADCAST)&packet,pszIP);
			break;
		case NETCMDID_USERQUIT:
			pThis->OnUserQuit((LPUSERQUIT)&packet,pszIP);
			break;
		case NETCMDID_USERCHAT:
			pThis->OnUserChat((LPUSERCHAT)&packet,pszIP);
			break;
			
		}
	}


	return 0;
}

//�����û��㲥����
BOOL UserServer::OnUserBroadcast(LPUSERBROADCAST pUserBroadcast, CHAR* pszIP)
{
	//���û���ӵ�UserView����
	if (m_pUserView != NULL)
	{
		m_pUserView->AddUser(pUserBroadcast->szName, pszIP, pUserBroadcast->szSign);
	}
	if (m_pChatView != NULL)
	{
		m_pChatView->AddUser(pszIP);
	}
	return TRUE;

}

//�����û������˳�
BOOL UserServer::OnUserQuit(LPUSERQUIT pUserQuit, CHAR* pszIP)
{
	if (m_pUserView != NULL)
	{
		m_pUserView->DelUser(pszIP);
	}
	if (m_pChatView != NULL)
	{
		m_pChatView->DelUser(pszIP);
	}

	
	return TRUE;
}

//������������
BOOL UserServer::OnUserChat(LPUSERCHAT pUserChat, CHAR* pszIP)
{
	if (pUserChat != NULL)
	{
		m_pChatView->AddChat(pUserChat->szChat, pszIP);
	}
	return TRUE;
}