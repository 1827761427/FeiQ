#ifndef _DEF_H_
#define _DEF_H_


#define PORT_USERSVR 5780
#define PORT_FILESVR 5781

//���ݰ��İ�ͷ
typedef struct _tagNetHeader
{
	DWORD  nVersion;
	DWORD  nCmdID;
	DWORD  nDataLength;
}NETHEADER, *LPNETHEADER;

//��׼UDP���ݱ�
typedef struct _tagUDPPacket
{
	NETHEADER	header;
	CHAR		szData[256];
}UDPPACKET,*LPUDPPACKET;

//�û��㲥����
#define NETCMDID_USERBROADCAST 1
typedef struct _tagUserBroadcast
{
	NETHEADER header;
	CHAR		szName[128];
	CHAR		szSign[128];
}USERBROADCAST,*LPUSERBROADCAST;

//�û������˳�����
#define NETCMDID_USERQUIT 2
typedef struct _tagUserQuit
{
	NETHEADER	header;
	DWORD		nExitCode;
}USERQUIT, *LPUSERQUIT;

//��������
#define NETCMDID_USERCHAT 3
typedef struct _tagUserChat
{
	NETHEADER	header;
	char		szChat[256];
}USERCHAT, *LPUSERCHAT;



//�����ļ�  
#define  NETCMDID_SENDFILE  4
typedef struct  _tagSendFile
{
	CHAR  szFileName[256];
	DWORD nFileLength;
}SENDFILE, *LPSENDFILE;

#endif