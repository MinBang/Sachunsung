
// SaClientView.cpp : CSaClientView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CSaClientView ����/�Ҹ�

CSaClientView::CSaClientView()
: m_Index(0)
, m_stdTime(0)
, m_Time(0)
, m_Stage(0)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

	IniGame();

}

CSaClientView::~CSaClientView()
{
}

BOOL CSaClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CSaClientView �׸���

void CSaClientView::OnDraw(CDC* pDC)
{
	CSaClientDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

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
			mem.TextOutW(50, 70, _T("����� �����Դϴ�."));
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
		//MessageBox(_T("���� ������ Ȯ���Ͽ��ּ���!!"));
		break;
	}

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &mem, 0, 0, SRCCOPY);
	ReleaseDC(pDC);
	pDC = NULL;
	mem.SelectObject(pOldBitmap);
	mem.DeleteDC();
	bitmap.DeleteObject();
}


// CSaClientView �μ�

BOOL CSaClientView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CSaClientView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CSaClientView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CSaClientView ����

#ifdef _DEBUG
void CSaClientView::AssertValid() const
{
	CView::AssertValid();
}

void CSaClientView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSaClientDoc* CSaClientView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSaClientDoc)));
	return (CSaClientDoc*)m_pDocument;
}
#endif //_DEBUG


// CSaClientView �޽��� ó����

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


			//Ŭ���Ѱ��� ������
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
	// ����� �Ⱥ���� üũ
	int count = 0;

	for (int i = 0; i<10; i++)
	{
		if (!m_Poses[i].m_Pos.empty())
		{
			count++;
		}
	}

	// �� ������� �ȱ׸�
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

	//���� �ʾҴµ� m_Flows �� �׷��� �� ���� �ٵǸ� clear���ش�.
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

	//���콺 ��ǥ
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

	// �÷��̰� ���۵��� ������ Ŭ�� �Ұ� -> ������ ���͸� �ľߵȴ�.
	if (0 == m_User.m_IsPlay && m_Stage != GAMING)
	{
		return;
	}

	//������ �Ѱų� 0���� Ŭ���ϸ� Ŭ������ ����.
	if (0 == m_Map[ypos][xpos] || xpos < 0 || MAP_SIZE < xpos || ypos < 0 || MAP_SIZE < ypos)
	{
		//MessageBox(_T("���� Ŭ�����ּ���"),_T("INFO"));
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

	//�Ѵ� ä������ ������ �����͸� ������.
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

		//���Ӹ� ��û.
		m_SaNet.SendGAMEMAP();

		SetTimer(1, 15, NULL);

		//���Ӹ��� ����
	/*	if (0 == m_SaNet.RecvRGAMEMAP())
		{
			m_Stage = WAIT;
			m_MousePOS.num = m_User.m_MyNum;

			
		}*/
	}
	else
	{
		MessageBox(_T("���� ������ Ȯ���Ͽ��ּ���!!"));
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
	���콺 ��ǥ �׸��� �κ� ���� Demo Ver�̴�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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

	// ��ΰ��� �ʱ�ȭ
	for (int i = 0; i<10; i++)
	{
		m_Flows[i] = 0;
		m_sFlows[i] = 0;
	}

	// ���콺 ����Ʈ �ʱ�ȭ
	m_MousePOS.x = 0;
	m_MousePOS.y = 0;

	for (int i = 0; i<2; i++)
	{
		for (int j = 0; j<4; j++)
		{
			m_rMousePOS[i][j].num = -1;
		}
	}

	// �������� �ʱ�ȭ
	m_User.m_Score = 0;
	m_User.m_IsPlay = 0;
	m_User.m_Combo = 0;
	m_User.m_MyNum = 0;
	m_User.m_RoomNum = 0;

	// ���� ���� �ʱ�ȭ
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
