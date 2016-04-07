// FileRecvDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FeiQ.h"
#include "FileRecvDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileRecvDlg dialog


CFileRecvDlg::CFileRecvDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileRecvDlg::IDD, pParent)
{
	//m_ClientSocket == INVALID_SOCKET;
	m_ClientSocket = INVALID_SOCKET;
}

CFileRecvDlg::~CFileRecvDlg()
{
	if (INVALID_SOCKET != m_ClientSocket)
	{
		closesocket(m_ClientSocket);
	}
}


void CFileRecvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileRecvDlg)
	DDX_Control(pDX, IDC_STC_Info, m_wndInfo);
	DDX_Control(pDX, IDC_PROGRESS1, m_wndProgress);
	DDX_Control(pDX, IDC_BTN_RECV, m_btnRecv);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileRecvDlg, CDialog)
	//{{AFX_MSG_MAP(CFileRecvDlg)
	ON_BN_CLICKED(IDC_BTN_RECV, OnBtnRecv)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_RECV_CLOSE, &CFileRecvDlg::OnBnClickedBtnRecvClose)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileRecvDlg message handlers

void CFileRecvDlg::OnBtnRecv() 
{
	// TODO: Add your control notification handler code here

	CFileDialog dlg(FALSE, NULL, m_sendFile.szFileName);//FALSE �����ļ�
	if ( IDOK != dlg.DoModal())
	{
		return;
	}
	
	GetDlgItem(IDC_BTN_RECV)->EnableWindow(FALSE);

	//�õ�·������
	m_strFilePath = dlg.GetPathName();
	
	//�����߳�
	AfxBeginThread(FileRecvThread, this);
	
}

//�������ݵ��߳�  �ֶζ�ȡ  ���������ķַ������
UINT CFileRecvDlg::FileRecvThread(LPVOID pParam)
{
	CFileRecvDlg* pThis = (CFileRecvDlg*)pParam;
	DWORD nFileLen = pThis->m_sendFile.nFileLength;

	//�����ļ�
	CFile file;
	if ( FALSE == file.Open(pThis->m_strFilePath,
		CFile::modeCreate | CFile::modeWrite))
	{
		return 0;
	}
	//���ý�����
	pThis->m_wndProgress.SetRange32(0, nFileLen);
	pThis->m_wndInfo.SetWindowText(_T("���ڽ�������......"));
	//��������
	CHAR szBuf[4096] = { 0 };
	DWORD nLeft = nFileLen;
	while (nLeft > 0)
	{

		//������ܵ�������
		DWORD nRecv = 4096;
		if (nLeft < nRecv)
		{
			nRecv = nLeft;
		}

		//��������
		pThis->RecvData(szBuf, nRecv);

		//д���ļ�
		file.Write(szBuf, nRecv);
		//����ʣ������
		nLeft = nLeft - nRecv;

		//���ý�����
		pThis->m_wndProgress.SetPos(nFileLen - nLeft);

	}
	pThis->m_wndInfo.SetWindowText(_T("�������ݳɹ�"));
	

	//�ر��ļ�
	file.Close();
	
	return 0;
}

//��������  ѭ������ ����һ�ν������
BOOL CFileRecvDlg::RecvData(LPVOID pData, DWORD nLen)
{

	LPSTR pTmpData = (LPSTR)pData;
	int nLeft = nLen;
	while (nLeft > 0)
	{
		int nRecv = recv(m_ClientSocket, pTmpData, nLeft,0);
		if (SOCKET_ERROR == nRecv)
		{
			return FALSE;
		}
		nLeft -= nRecv;

		pTmpData += nRecv;

	}

	return TRUE;
}

BOOL CFileRecvDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	//���ܰ�ͷ�Լ����͵��ļ���Ϣ
	NETHEADER header = { 0 };
	RecvData((LPSTR)&header, sizeof(header));
	RecvData((LPSTR)&m_sendFile, sizeof(m_sendFile));

	//������ļ���Ϣ�����Խ��ļ���Ϣ��ʾ�ڴ�����
	SetWindowText(m_strIP);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CFileRecvDlg::OnBnClickedBtnRecvClose()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileRecvDlg::OnOK();
}
