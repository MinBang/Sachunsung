
// SaClientView.h : CSaClientView 클래스의 인터페이스
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
protected: // serialization에서만 만들어집니다.
	CSaClientView();
	DECLARE_DYNCREATE(CSaClientView)

// 특성입니다.
public:
	CSaClientDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CSaClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:

	int m_Time;
	int m_stdTime;

	////////////////////////

	SaNet m_SaNet; // 네트워크 통신 부분을 담당하는 클래스
	int(*m_Map)[MAP_SIZE]; // 맵 포인터

	S_USER m_User; // 유저들의 정보를 담고있음.
	S_JOIN m_Join; // 접속 정보를 담고 있음.

	int m_Index; // 골인 된 것을 담을 Flows들의 Index Number -> SaNet에서 초기화 함
	int m_Stage; // 현재 스테이지 Index

	///////////////////// DrawRoute의 변수	
	S_POSES m_Poses[10]; // 전체 그려야 될 정보가 여기 있다.

	int m_Flows[10]; // 그려야 될 갯수
	int m_sFlows[10]; // 출발 하는 곳

	//////////////////////////////////	
	S_ONCLICK m_Click[2]; // 내가 클릭한 곳의 좌표
	S_ONCLICK m_dClick[2]; // 상대가 클리한 곳의 좌표

	/////////////////////////////////
	S_POS m_MousePOS; // 내 마우스 포인트
	S_POS m_rMousePOS[2][4]; //모든 유저들의 마우스 포인트

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

#ifndef _DEBUG  // SaClientView.cpp의 디버그 버전
inline CSaClientDoc* CSaClientView::GetDocument() const
   { return reinterpret_cast<CSaClientDoc*>(m_pDocument); }
#endif

