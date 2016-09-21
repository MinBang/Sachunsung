
// SaClientView.h : CSaClientView Ŭ������ �������̽�
//

#pragma once

#include "SaNet.h"
#include "atlimage.h"

typedef struct _POSES
{
	vector<S_POS> m_Pos;
}S_POSES;

typedef struct _USER
{
	CString m_Name;
	int m_MyNum;
	int m_RoomNum;

	int m_Score;
	int m_Combo;

	int m_IsPlay;
}S_USER;

typedef struct _JOIN
{
	CString m_Ip;
	int m_Port;
}S_JOIN;

class CSaClientView : public CView
{
protected: // serialization������ ��������ϴ�.
	CSaClientView();
	DECLARE_DYNCREATE(CSaClientView)

// Ư���Դϴ�.
public:
	CSaClientDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CSaClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:

	int m_Time;
	int m_stdTime;

	////////////////////////

	SaNet m_SaNet; // ��Ʈ��ũ ��� �κ��� ����ϴ� Ŭ����
	int(*m_Map)[MAP_SIZE]; // �� ������

	S_USER m_User; // �������� ������ �������.
	S_JOIN m_Join; // ���� ������ ��� ����.

	int m_Index; // ���� �� ���� ���� Flows���� Index Number -> SaNet���� �ʱ�ȭ ��
	int m_Stage; // ���� �������� Index

	///////////////////// DrawRoute�� ����	
	S_POSES m_Poses[10]; // ��ü �׷��� �� ������ ���� �ִ�.

	int m_Flows[10]; // �׷��� �� ����
	int m_sFlows[10]; // ��� �ϴ� ��

	//////////////////////////////////	
	S_ONCLICK m_Click[2]; // ���� Ŭ���� ���� ��ǥ
	S_ONCLICK m_dClick[2]; // ��밡 Ŭ���� ���� ��ǥ

	/////////////////////////////////
	S_POS m_MousePOS; // �� ���콺 ����Ʈ
	S_POS m_rMousePOS[2][4]; //��� �������� ���콺 ����Ʈ

	int IniClick(void);
	int IniClick(int re);

private:
	void IniGame();
	int DrawMap(CDC* pDC);
	int DrawRoute(CDC* pDC);
	int DrawrMouses(CDC* pDC);
	void DrawTap(CDC* pDC);
	void IniImage();

	////////////////////////////

	CImage m_Card1;
	CImage m_Card2;
	CImage m_Card3;
	CImage m_Card4;
	CImage m_Card5;
	CImage m_Card6;
	CImage m_Card7;
	CImage m_Card8;

	CImage m_BGMap;
	CImage m_Mouse;

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // SaClientView.cpp�� ����� ����
inline CSaClientDoc* CSaClientView::GetDocument() const
   { return reinterpret_cast<CSaClientDoc*>(m_pDocument); }
#endif

