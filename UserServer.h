// UserServer.h: interface for the UserServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERSERVER_H__01328ECD_C819_490A_9E1F_C29BFCDC3642__INCLUDED_)
#define AFX_USERSERVER_H__01328ECD_C819_490A_9E1F_C29BFCDC3642__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "ChatView.h"
#include "UserView.h"
class UserServer  
{
public:
	UserServer();
	virtual ~UserServer();

public:

	//��ʼ��User������
	BOOL InitServer();
	//�������ݵ��߳�
	static UINT UserThread(LPVOID pParam);
	//�����û��㲥���������� ����˰�������ʾ�� UserView��ͼ��������
	BOOL OnUserBroadcast(LPUSERBROADCAST pUserBroadcast,CHAR* pszIP);

	//�����û������˳� ����˰�UserView��ͼ�� list�б������Ӧ���û�ɾ��
	BOOL OnUserQuit(LPUSERQUIT pUserQuit, CHAR* pszIP);

	//������������
	BOOL OnUserChat(LPUSERCHAT pUserChat, CHAR* pszIP);

public:
	SOCKET			m_svrSocket;
	CUserView*		m_pUserView;
	CChatView*		m_pChatView;

};

#endif // !defined(AFX_USERSERVER_H__01328ECD_C819_490A_9E1F_C29BFCDC3642__INCLUDED_)
