// UserClient.h: interface for the UserClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERCLIENT_H__AC7F1E91_A33B_45C7_A623_F18A6B0B60E9__INCLUDED_)
#define AFX_USERCLIENT_H__AC7F1E91_A33B_45C7_A623_F18A6B0B60E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class UserClient  
{
public:
	UserClient();
	virtual ~UserClient();

public:
	//��ʼ���ͻ���
	BOOL InitClient();
	//�㲥����
	BOOL Broadcast();
	//��������
	BOOL SendData(CHAR* psxData,UINT nLen,LPCSTR strIP = NULL);

	//�����ر��˳�����
	BOOL UserQuit();

		//����
	BOOL SendChat(CString strIP, CString strData, BOOL bBroadcast = TRUE);

public:
	SOCKET m_ClientSocket;

};

#endif // !defined(AFX_USERCLIENT_H__AC7F1E91_A33B_45C7_A623_F18A6B0B60E9__INCLUDED_)
