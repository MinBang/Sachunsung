// SaNet.cpp : implementation file
//

#include "stdafx.h"
#include "SaClient.h"
#include "SaNet.h"

#include "SaClientDoc.h"
#include "SaClientView.h"

// SaNet

SaNet::SaNet()
{
}

SaNet::~SaNet()
{
}


// SaNet member functions

void SaNet::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	S_H h;
	int hlen = sizeof(h);

	Receive(&h, hlen);

	if (CMD_SC_RADATA == h.cmd)
	{
		RecvRADATA();
	}
	else if (CMD_SC_RDATA == h.cmd)
	{
		RecvRDATA();
	}
	else if (CMD_SC_RMOUSEPOS == h.cmd)
	{
		RecvRMOUSEPOS();
	}
	else if (CMD_SC_RSTART == h.cmd)
	{
		m_View->m_User.m_IsPlay = 1;
		m_View->m_Stage = GAMING;
	}
	else if (CMD_SC_MAXUSER == h.cmd)
	{
		AfxMessageBox(_T("MaxUser!!"));
		exit(1);
	}
	else if (CMD_SC_COLLISION == h.cmd)
	{
		m_View->IniClick(-1);

		//SendGAMEMAP();
	}
	else if (CMD_SC_ALREADYPLAY == h.cmd)
	{
		AfxMessageBox(_T("Already Play!!"));
		exit(1);
	}
	if (CMD_SC_RGAMEMAP == h.cmd)
	{
		RecvRGAMEMAP();
	}


	//CSocket::OnReceive(nErrorCode);
}

int SaNet::SendData(int sx, int sy, int dx, int dy)
{
	S_H h;
	S_DATA sdata;

	int hlen = sizeof(h);
	int dlen = sizeof(sdata);

	h.cmd = CMD_CS_DATA;
	h.len = dlen;

	sdata.sx = sx;
	sdata.sy = sy;
	sdata.dx = dx;
	sdata.dy = dy;

	char buf[1024];

	memcpy(buf, &h, hlen);
	memcpy(buf + hlen, &sdata, dlen);

	Send(buf, hlen + dlen);

	return 0;
}

int SaNet::SendStart()
{
	S_H h;

	h.cmd = CMD_CS_START;
	h.len = m_View->m_User.m_MyNum;

	char buf[1024];

	memcpy(buf, &h, sizeof(h));

	Send(buf, sizeof(h));

	return 0;
}

int SaNet::SendGAMEMAP(void)
{
	S_H h;

	int hlen = sizeof(h);

	h.cmd = CMD_CS_GAMEMAP;
	h.len = 0;

	char buf[1024];

	memcpy(buf, &h, hlen);

	Send(buf, hlen);

	return 0;
}

int SaNet::SendMousePOS(S_POS t_Pos)
{
	S_H h;

	int hlen = sizeof(h);
	int dlen = sizeof(t_Pos);

	h.cmd = CMD_CS_MOUSEPOS;
	h.len = dlen;

	char buf[1024];

	memcpy(buf, &h, hlen);
	memcpy(buf + hlen, &t_Pos, dlen);

	Send(buf, hlen + dlen);

	return 0;
}

int SaNet::RecvRADATA()
{
	S_RADATA rdata;
	Receive(&rdata, sizeof(rdata));

	if (GAME_END == rdata.re)
	{
		m_View->m_Stage = END;
		m_View->m_User.m_IsPlay = false;
	}

	int size = rdata.pos[0].num;

	//m_View->m_User.m_Score = rdata.score;
	//m_View->m_User.m_Combo = rdata.combo;

	int index = m_View->m_Index;

	m_View->m_Flows[index] = size - 1;
	m_View->m_sFlows[index] = size - 1;

	for (int j = 0; j<size; j++)
	{
		m_View->m_Poses[index].m_Pos.push_back(rdata.pos[j]);
	}

	m_View->m_Index = (m_View->m_Index + 1) % 10;

	CString str;

	if (GOAL == rdata.re || GAME_END == rdata.re)
	{
		m_View->m_dClick[SOUR].x = rdata.sx;
		m_View->m_dClick[SOUR].y = rdata.sy;
		m_View->m_dClick[SOUR].isUsing = true;

		m_View->m_dClick[DEST].x = rdata.dx;
		m_View->m_dClick[DEST].y = rdata.dy;
		m_View->m_dClick[DEST].isUsing = true;

		for (int i = 0; i < 2; i++)
		{
			if (m_View->m_Click[i].x == rdata.sx &&
				m_View->m_Click[i].y == rdata.sy)
			{
				m_View->m_Click[i].x = 0;
				m_View->m_Click[i].y = 0;
				m_View->m_Click[i].isUsing = false;
			}
			else if (m_View->m_Click[i].x == rdata.dx &&
				m_View->m_Click[i].y == rdata.dy)
			{
				m_View->m_Click[i].x = 0;
				m_View->m_Click[i].y = 0;
				m_View->m_Click[i].isUsing = false;
			}
		}
	}

	m_View->IniClick(rdata.re);

	return 0;
}

int SaNet::RecvRDATA()
{
	S_RDATA rdata;
	Receive(&rdata, sizeof(rdata));

	if (GAME_END == rdata.re)
	{
		m_View->m_Stage = END;
		m_View->m_User.m_IsPlay = false;
	}

	int size = rdata.pos[0].num;

	m_View->m_User.m_Score = rdata.score;
	m_View->m_User.m_Combo = rdata.combo;

	int index = m_View->m_Index;

	m_View->m_Flows[index] = size - 1;
	m_View->m_sFlows[index] = size - 1;

	for (int j = 0; j<size; j++)
	{
		m_View->m_Poses[index].m_Pos.push_back(rdata.pos[j]);
	}

	m_View->IniClick(rdata.re);

	m_View->m_Index = (m_View->m_Index + 1) % 10;

	return 0;
}

int SaNet::RecvRGAMEMAP(void)
{
	S_RGAMEMAP rdata;
	Receive(&rdata, sizeof(rdata));

	memcpy(m_View->m_Map, rdata.map, sizeof(rdata.map));
	m_View->m_User.m_MyNum = rdata.num;

	m_View->m_MousePOS.num = m_View->m_User.m_MyNum;

	return 0;
}

int SaNet::RecvRMOUSEPOS(void)
{
	S_RMOUSEPOS rdata;
	Receive(&rdata, sizeof(rdata));

	for (int i = 0; i<4; i++)
	{
		m_View->m_rMousePOS[SOUR][i] = rdata.pos[i];

	}

	return 0;
}