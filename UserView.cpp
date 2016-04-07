// UserView.cpp : implementation file
//

#include "stdafx.h"
#include "FeiQ.h"
#include "UserView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserView

IMPLEMENT_DYNCREATE(CUserView, CListView)

CUserView::CUserView()
{
}

CUserView::~CUserView()
{
}


BEGIN_MESSAGE_MAP(CUserView, CListView)
	//{{AFX_MSG_MAP(CUserView)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserView drawing

void CUserView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CUserView diagnostics

#ifdef _DEBUG
void CUserView::AssertValid() const
{
	CListView::AssertValid();
}

void CUserView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUserView message handlers

int CUserView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	ModifyStyle(0, LVS_REPORT);

	CListCtrl& theCtrl = GetListCtrl();
	theCtrl.InsertColumn(0, _T("���������"), LVCFMT_LEFT, 100);
	theCtrl.InsertColumn(1, _T("IP��ַ"), LVCFMT_LEFT, 100);
	theCtrl.InsertColumn(2, _T("ǩ��"), LVCFMT_LEFT, 230);


	SetTimer(2,1000*10,NULL);
	return 0;
}
//���յ�����Ϣ��ӵ��û���Ϣ
void CUserView::AddUser(CString strName, CString strIP, CString strSign)
{
	
	CListCtrl& theCtrl = GetListCtrl();
	int nItem = theCtrl.GetItemCount();
	if (-1 != FindUser(strIP))
	{
		theCtrl.SetItemData(nItem, 1); //�б��������  �㲥���������� ��heartbeat��Ϊ1 ��ʾ���
		return;
	}

	nItem = theCtrl.InsertItem(nItem, strName);
	theCtrl.SetItemText(nItem, 1, strIP);
	theCtrl.SetItemText(nItem, 2, strSign);
	theCtrl.SetItemData(nItem, 1);  //�¼ӵ��û�  heartbeat��Ϊ1  ��ʾ���
}

int CUserView::FindUser(CString strIP)
{
	CListCtrl & theCtrl = GetListCtrl();
	int nCount = theCtrl.GetItemCount();
	for (int nItem = 0; nItem < nCount; nItem++)
	{
		CString strItemIP = theCtrl.GetItemText(nItem, 1); //�õ�IP��ַ
		if ( 0 == strItemIP.CompareNoCase(strIP))
		{
			return nItem;
		}
	}
	return -1;
}

void CUserView::DelUser(CString strIP)
{
	//����ָ��IP���û�
	int nItem = FindUser(strIP);
	if ( nItem == -1)
	{
		return;
	}
	//ɾ���û�
	CListCtrl &theCtrl = GetListCtrl();
	theCtrl.DeleteItem(nItem);
}

void CUserView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//�������������ݱ�־
	
	if (nIDEvent != 2)
	{
		return;
	}

	CListCtrl& theCtrl = GetListCtrl();

	int nCount = theCtrl.GetItemCount();

	//AfxMessageBox(_T("nCount = ")+nCount);

	for (int nItem = nCount - 1; nItem >= 0; nItem--)
	{
		//��ȡheartbeat��ֵ
		DWORD nData = theCtrl.GetItemData(nItem);
		if (nData > 0)
		{
			theCtrl.SetItemData(nItem, 0);//ÿ��һ��ʱ��  ��ȡheartbeatֵ  ���Ϊ1��ʾ��� ��Ϊ0  �´��յ������� ��ADDUser ����Ϊ1
		}
		else//���heartbeatֵ�ϴ���Ϊ0����λ���Ϊ0��˵����AddUser����û���յ���Item�������� �Ѿ��Ͽ�  ȥ��
		{
			theCtrl.DeleteItem(nItem);
		}
	}

	CListView::OnTimer(nIDEvent);
}


void CUserView::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CListCtrl& theCtrl  = GetListCtrl();
	
	//int nItem = (int)theCtrl.GetFirstSelectedItemPosition() - 1;
	int nItem = (int)theCtrl.GetFirstSelectedItemPosition();
	CString strData = theCtrl.GetItemText(nItem,0);
	
	AfxMessageBox(strData);
	*pResult = 0;
}

void CUserView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
