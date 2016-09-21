
// SaClientView.cpp : CSaClientView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SaClient.h"
#endif

#include "SaClientDoc.h"
#include "SaClientView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int g_Map1[MAP_SIZE][MAP_SIZE] = { 0, };

// CSaClientView

IMPLEMENT_DYNCREATE(CSaClientView, CView)

BEGIN_MESSAGE_MAP(CSaClientView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CSaClientView 생성/소멸

CSaClientView::CSaClientView()
: m_Index(0)
, m_stdTime(0)
, m_Time(0)
, m_Stage(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.

	IniGame();

}

CSaClientView::~CSaClientView()
{
}

BOOL CSaClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSaClientView 그리기

void CSaClientView::OnDraw(CDC* pDC)
{
	CSaClientDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	CRect rect;
	GetClientRect(&rect);

	CDC mem;
	CBitmap *pOldBitmap, bitmap;
	mem.CreateCompatibleDC(pDC);
	bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	pOldBitmap = mem.SelectObject(&bitmap);
	mem.PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);

	switch (m_Stage)
	{
	case WAIT:
		mem.TextOutW(50, 50, _T("Press Enter Key!!"));
		if (0 == m_User.m_MyNum)
		{
			mem.TextOutW(50, 70, _T("당신은 방장입니다."));
		}
		break;

		break;
	case GAMING:
		DrawMap(&mem);

		DrawRoute(&mem);

		DrawTap(&mem);

		DrawrMouses(&mem);
		break;
	case END:
		mem.TextOutW(50, 50, _T("GameEnd!!"));

	default:
		//MessageBox(_T("서버 연결을 확인하여주세요!!"));
		break;
	}

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &mem, 0, 0, SRCCOPY);
	ReleaseDC(pDC);
	pDC = NULL;
	mem.SelectObject(pOldBitmap);
	mem.DeleteDC();
	bitmap.DeleteObject();
}


// CSaClientView 인쇄

BOOL CSaClientView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSaClientView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSaClientView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CSaClientView 진단

#ifdef _DEBUG
void CSaClientView::AssertValid() const
{
	CView::AssertValid();
}

void CSaClientView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSaClientDoc* CSaClientView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSaClientDoc)));
	return (CSaClientDoc*)m_pDocument;
}
#endif //_DEBUG


// CSaClientView 메시지 처리기

int CSaClientView::DrawMap(CDC* pDC)
{
	int xpos, ypos;

	m_BGMap.TransparentBlt(pDC->m_hDC, 0, 0, 1000, 1000);

	for (int y = 0; y<MAP_SIZE; y++)
	{
		for (int x = 0; x<MAP_SIZE; x++)
		{
			ypos = y * CARD_HEIGHT;
			xpos = x * CARD_WIDTH;

			if (0 != m_Map[y][x])
			{
				//pDC->Rectangle(MAP_STARTX + xpos, MAP_STARTY + ypos, MAP_STARTX + xpos+CARD_WIDTH - 1, MAP_STARTY + ypos+CARD_HEIGHT - 1);

				int term = 3;

				switch (m_Map[y][x])
				{
				case 1:
					m_Card1.TransparentBlt(pDC->m_hDC, MAP_STARTX + xpos, MAP_STARTY + ypos,
						CARD_WIDTH - term, CARD_HEIGHT - term);
					break;
				case 2:
					m_Card2.TransparentBlt(pDC->m_hDC, MAP_STARTX + xpos, MAP_STARTY + ypos,
						CARD_WIDTH - term, CARD_HEIGHT - term);
					break;
				case 3:
					m_Card3.TransparentBlt(pDC->m_hDC, MAP_STARTX + xpos, MAP_STARTY + ypos,
						CARD_WIDTH - term, CARD_HEIGHT - term);
					break;
				case 4:
					m_Card4.TransparentBlt(pDC->m_hDC, MAP_STARTX + xpos, MAP_STARTY + ypos,
						CARD_WIDTH - term, CARD_HEIGHT - term);
					break;
				case 5:
					m_Card5.TransparentBlt(pDC->m_hDC, MAP_STARTX + xpos, MAP_STARTY + ypos,
						CARD_WIDTH - term, CARD_HEIGHT - term);
					break;
				case 6:
					m_Card6.TransparentBlt(pDC->m_hDC, MAP_STARTX + xpos, MAP_STARTY + ypos,
						CARD_WIDTH - term, CARD_HEIGHT - term);
					break;
				case 7:
					m_Card7.TransparentBlt(pDC->m_hDC, MAP_STARTX + xpos, MAP_STARTY + ypos,
						CARD_WIDTH - term, CARD_HEIGHT - term);
					break;
				case 8:
					m_Card8.TransparentBlt(pDC->m_hDC, MAP_STARTX + xpos, MAP_STARTY + ypos,
						CARD_WIDTH - term, CARD_HEIGHT - term);
					break;
				default:
					break;
				}
			}


			//클릭한곳이 빨갛게
			for (int i = 0; i<2; i++)
			{
				if (true == m_Click[i].isUsing && x == m_Click[i].x && y == m_Click[i].y)
				{
					CPen pen;
					pen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
					CPen* pOldPen = pDC->SelectObject(&pen);

					pDC->MoveTo(MAP_STARTX + xpos, MAP_STARTY + ypos);
					pDC->LineTo(MAP_STARTX + xpos + CARD_WIDTH, MAP_STARTY + ypos);

					pDC->MoveTo(MAP_STARTX + xpos + CARD_WIDTH, MAP_STARTY + ypos);
					pDC->LineTo(MAP_STARTX + xpos + CARD_WIDTH, MAP_STARTY + ypos + CARD_HEIGHT);

					pDC->MoveTo(MAP_STARTX + xpos + CARD_WIDTH, MAP_STARTY + ypos + CARD_HEIGHT);
					pDC->LineTo(MAP_STARTX + xpos, MAP_STARTY + ypos + CARD_HEIGHT);

					pDC->MoveTo(MAP_STARTX + xpos, MAP_STARTY + ypos + CARD_HEIGHT);
					pDC->LineTo(MAP_STARTX + xpos, MAP_STARTY + ypos);

					pDC->SelectObject(pOldPen);
					pen.DeleteObject();
				}
			}

			/*CString str;
			str.Format(_T("%d"), m_Map[y][x]);

			if(0 != m_Map[y][x])
			{
			pDC->TextOutW(MAP_STARTX + xpos+15, MAP_STARTY + ypos+15, str);
			}*/
		}
	}

	return 0;
}

int CSaClientView::DrawRoute(CDC* pDC)
{
	// 몇군데가 안비었나 체크
	int count = 0;

	for (int i = 0; i<10; i++)
	{
		if (!m_Poses[i].m_Pos.empty())
		{
			count++;
		}
	}

	// 다 비었으면 안그림
	if (0 == count)
	{
		return 0;
	}

	for (int i = 0; i<10; i++)
	{
		if (!m_Poses[i].m_Pos.empty())
		{
			m_Flows[i]--;

			for (int j = m_sFlows[i]; m_Flows[i] < j; j--)
			{
				int xpos = m_Poses[i].m_Pos[j].x * CARD_WIDTH;
				int ypos = m_Poses[i].m_Pos[j].y * CARD_HEIGHT;

				CString str;
				str.Format(_T("%d"), m_Poses[i].m_Pos[j].num);

				CPen pen;
				pen.CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
				CPen* pOldPen = pDC->SelectObject(&pen);

				pDC->MoveTo(MAP_STARTX + xpos, MAP_STARTY + ypos);
				pDC->LineTo(MAP_STARTX + xpos + CARD_WIDTH, MAP_STARTY + ypos);

				pDC->MoveTo(MAP_STARTX + xpos + CARD_WIDTH, MAP_STARTY + ypos);
				pDC->LineTo(MAP_STARTX + xpos + CARD_WIDTH, MAP_STARTY + ypos + CARD_HEIGHT);

				pDC->MoveTo(MAP_STARTX + xpos + CARD_WIDTH, MAP_STARTY + ypos + CARD_HEIGHT);
				pDC->LineTo(MAP_STARTX + xpos, MAP_STARTY + ypos + CARD_HEIGHT);

				pDC->MoveTo(MAP_STARTX + xpos, MAP_STARTY + ypos + CARD_HEIGHT);
				pDC->LineTo(MAP_STARTX + xpos, MAP_STARTY + ypos);

				//pDC->Rectangle(MAP_STARTX + xpos, MAP_STARTY + ypos, MAP_STARTX + xpos + CARD_WIDTH, MAP_STARTY + ypos + CARD_HEIGHT);
				//pDC->TextOutW(MAP_STARTX + xpos+15, MAP_STARTY + ypos, str);

				pDC->SelectObject(pOldPen);
				pen.DeleteObject();
			}
		}
	}

	//비지 않았는데 m_Flows 즉 그려야 될 것이 다되면 clear해준다.
	for (int i = 0; i<10; i++)
	{
		if (!m_Poses[i].m_Pos.empty())
		{
			if (m_Flows[i] < 0)
			{
				m_Poses[i].m_Pos.clear();
				m_sFlows[i] = 0;
			}
		}
	}

	return 0;
}

void CSaClientView::DrawTap(CDC* pDC)
{
	CString str;

	//마우스 좌표
	for (int i = 0; i<2; i++)
	{
		CString str;
		str.Format(_T("X : %d  | Y: %d"), m_Click[i].x, m_Click[i].y);

		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->TextOutW(750, (i + 1) * 20, str);
	}

	str.Format(_T("Score : %d | Combo : %d"), m_User.m_Score, m_User.m_Combo);
	pDC->TextOutW(750, 70, str);

	str.Format(_T("isPlay : %d"), m_User.m_IsPlay);
	pDC->TextOutW(750, 100, str);

	str.Format(_T("Time : %d"), m_Time);
	pDC->TextOutW(750, 130, str);
}


int CSaClientView::IniClick(int re)
{
	/*
	GOAL        20
	NO_WAY      21
	GAME_END    22

	SAME_CLICK  30
	NOT_SAME    31
	*/

	if (NO_WAY == re || NOT_SAME == re)
	{
		m_Click[SOUR].x = m_Click[DEST].x;
		m_Click[SOUR].y = m_Click[DEST].y;
		m_Click[DEST].x = 0;
		m_Click[DEST].y = 0;
		m_Click[DEST].isUsing = false;
	}
	else if (SAME_CLICK == re)
	{
		m_Click[DEST].isUsing = false;
		m_Click[DEST].x = 0;
		m_Click[DEST].y = 0;
	}
	else if (GOAL == re || GAME_END == re)
	{
		int sx, sy, dx, dy;

		if (false == m_dClick[SOUR].isUsing)
		{
			sx = m_Click[SOUR].x;
			sy = m_Click[SOUR].y;

			dx = m_Click[DEST].x;
			dy = m_Click[DEST].y;

			for (int i = 0; i<2; i++)
			{
				m_Click[i].isUsing = false;
				m_Click[i].x = 0;
				m_Click[i].y = 0;
			}
		}
		else
		{
			sx = m_dClick[SOUR].x;
			sy = m_dClick[SOUR].y;

			dx = m_dClick[DEST].x;
			dy = m_dClick[DEST].y;

			m_dClick[SOUR].isUsing = false;
			m_dClick[DEST].isUsing = false;
		}

		m_Map[sy][sx] = 0;
		m_Map[dy][dx] = 0;
	}
	else
	{
		for (int i = 0; i<2; i++)
		{
			m_Click[i].isUsing = false;
			m_Click[i].x = 0;
			m_Click[i].y = 0;
		}
	}

	return 0;
}

int CSaClientView::IniClick(void)
{
	for (int i = 0; i<2; i++)
	{
		m_Click[i].isUsing = false;
		m_Click[i].x = 0;
		m_Click[i].y = 0;

		m_dClick[i].isUsing = false;
		m_dClick[i].x = 0;
		m_dClick[i].y = 0;
	}

	return 0;
}

void CSaClientView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	int xpos = (point.x - MAP_STARTX) / CARD_WIDTH;
	int ypos = (point.y - MAP_STARTY) / CARD_HEIGHT;

	// 플레이가 시작되지 않으면 클릭 불가 -> 방장이 엔터를 쳐야된다.
	if (0 == m_User.m_IsPlay && m_Stage != GAMING)
	{
		return;
	}

	//범위를 넘거나 0번을 클릭하면 클릭되지 않음.
	if (0 == m_Map[ypos][xpos] || xpos < 0 || MAP_SIZE < xpos || ypos < 0 || MAP_SIZE < ypos)
	{
		//MessageBox(_T("블럭을 클릭해주세요"),_T("INFO"));
		return;
	}

	for (int i = 0; i<2; i++)
	{
		if (false == m_Click[i].isUsing)
		{
			m_Click[i].isUsing = true;

			m_Click[i].x = xpos;
			m_Click[i].y = ypos;

			break;
		}
	}

	//둘다 채워지면 서버로 데이터를 보낸다.
	if (true == m_Click[DEST].isUsing)
	{
		int sx = m_Click[SOUR].x;
		int sy = m_Click[SOUR].y;

		int dx = m_Click[DEST].x;
		int dy = m_Click[DEST].y;

		m_SaNet.SendData(sx, sy, dx, dy);
	}

	CView::OnLButtonDown(nFlags, point);
}

int CSaClientView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	m_SaNet.Create();

	if (TRUE == m_SaNet.Connect(m_Join.m_Ip, m_Join.m_Port))
	{
		MessageBox(_T("Success Connect!!"));

		//게임맵 요청.
		m_SaNet.SendGAMEMAP();

		SetTimer(1, 15, NULL);

		//게임맵이 오면
	/*	if (0 == m_SaNet.RecvRGAMEMAP())
		{
			m_Stage = WAIT;
			m_MousePOS.num = m_User.m_MyNum;

			
		}*/
	}
	else
	{
		MessageBox(_T("서버 연결을 확인하여주세요!!"));
		exit(1);
	}

	return 0;
}


void CSaClientView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	Invalidate(FALSE);

	//Sleep(30);

	//m_SaNet.SendMousePOS(m_MousePOS);

	if (GAMING == m_Stage)
	{
		m_stdTime++;

		if (30 == m_stdTime)
		{
			m_Time++;
			m_stdTime = 0;
		}
	}

	//CView::OnTimer(nIDEvent);
}

void CSaClientView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	m_MousePOS.x = point.x;
	m_MousePOS.y = point.y;

	CView::OnMouseMove(nFlags, point);
}

int CSaClientView::DrawrMouses(CDC* pDC)
{
	/*
	마우스 좌표 그리는 부분 아직 Demo Ver이다.
	*/
	for (int i = 0; i<4; i++)
	{
		if (i != m_User.m_MyNum && -1 != m_rMousePOS[SOUR][i].num)
		{
			//pDC->Ellipse(m_rMousePOS[SOUR][i].x, m_rMousePOS[SOUR][i].y, m_rMousePOS[SOUR][i].x+30, m_rMousePOS[SOUR][i].y+30);
			m_Mouse.TransparentBlt(pDC->m_hDC, m_rMousePOS[SOUR][i].x, m_rMousePOS[SOUR][i].y, 40, 40, RGB(255, 255, 255));
		}
	}

	return 0;
}


void CSaClientView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (0 == m_User.m_MyNum)
	{
		if (VK_RETURN == nChar)
		{
			m_Stage = GAMING;

			m_SaNet.SendStart();
		}
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CSaClientView::IniGame()
{
	m_SaNet.m_View = this;
	m_Map = g_Map1;

	IniClick();

	///////////////////

	// 경로갯수 초기화
	for (int i = 0; i<10; i++)
	{
		m_Flows[i] = 0;
		m_sFlows[i] = 0;
	}

	// 마우스 포인트 초기화
	m_MousePOS.x = 0;
	m_MousePOS.y = 0;

	for (int i = 0; i<2; i++)
	{
		for (int j = 0; j<4; j++)
		{
			m_rMousePOS[i][j].num = -1;
		}
	}

	// 유저정보 초기화
	m_User.m_Score = 0;
	m_User.m_IsPlay = 0;
	m_User.m_Combo = 0;
	m_User.m_MyNum = 0;
	m_User.m_RoomNum = 0;

	// 접속 정보 초기화
	//m_Join.m_Ip.Format(_T("1.209.148.169"));

	m_Join.m_Ip.Format(_T("127.0.0.1"));
	m_Join.m_Port = 2016;

	IniImage();
}

void CSaClientView::IniImage()
{
	m_Card1.Load(_T("img/1.jpg"));
	m_Card2.Load(_T("img/2.jpg"));
	m_Card3.Load(_T("img/3.jpg"));
	m_Card4.Load(_T("img/4.jpg"));
	m_Card5.Load(_T("img/5.jpg"));
	m_Card6.Load(_T("img/6.jpg"));
	m_Card7.Load(_T("img/7.jpg"));
	m_Card8.Load(_T("img/8.jpg"));

	m_BGMap.Load(_T("img/bgImage.jpg"));
	m_Mouse.Load(_T("img/Mouse.jpg"));
}
