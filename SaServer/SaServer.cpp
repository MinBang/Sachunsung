// SaServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Lib/NetLib.h"
#include "KGame.h"

#define MAX_ROOM   10
#define MAX_USER    4

#define ROOM_NUMBER 0

typedef struct _USER
{
	SOCKET s;

	char m_Name[20];
	int m_Score;
	int m_Combo;

	bool isUsing;
}S_USER;

typedef struct _ROOM
{
	char roomName[30];
	int roomNumber;	
	int userCount;

	bool isPlay;
}S_ROOM;

S_USER g_Users[MAX_ROOM][MAX_USER];
S_ROOM g_Room[MAX_ROOM];

CRITICAL_SECTION g_Cs;

S_POS s_MousePOS[4]; // 유저 마우스 정보 4개를 저장하는 곳
S_USER* p_User = NULL;

/////////////////////////////////////////

int RunGame(SOCKET c, SOCKADDR_IN* caddr);

void IniServer(WSAData* wsa);
void EndServer();

S_USER* FindEmptyUser();
int FindUser(SOCKET c);
S_USER* FindPUser(SOCKET c);
void LeaveUser(SOCKET c);
void DrawMapState(int(*t_Map)[MAP_SIZE], int re, int size);

////////////////////////////////////////

int SendRStart(SOCKET c);
int SendRDATA(SOCKET s);
int SendRGAMEMAP(SOCKET c, KGame* Game);
int OnRoomPlay(SOCKET c, int num);

void IniMousePOS();
int SendMousePOS(SOCKET c);
int RecvnMousePOS(SOCKET c);

int SendMaxClient(SOCKET c);



///////////////////////////////////////

S_USER* FindPUser(SOCKET c)
{
	S_USER* p_User = NULL;

	for (int i=0;i<MAX_ROOM;i++)
	{
		for (int j=0;j<MAX_USER;j++)
		{
			if (true == g_Users[i][j].isUsing && c == g_Users[i][j].s)
			{
				p_User = &g_Users[i][j];
			}
		}
	}

	return p_User;
}

int SendAlreadyPlay(SOCKET c)
{
	S_H h;

	h.cmd = CMD_SC_ALREADYPLAY;
	h.len = 0;

	char buf[1024];

	memcpy(buf, &h, sizeof(h));

	send(c, buf, sizeof(h), 0);
	
	return 0;
}

int RunGame(SOCKET c, SOCKADDR_IN* caddr)
{
	int re;

	KGame m_Game(ROOM_NUMBER);
	//S_USER* p_User;

	if (true == g_Room[ROOM_NUMBER].isPlay)
	{
		SendAlreadyPlay(c);
	}
	
	if (0 == m_Game.CheckGameOver())
	{
		m_Game.IniMap();
		m_Game.MakeMap();
	}	

	// 유저 중복체크 해준다.
	if (-1 == FindUser(c))
	{
		p_User = FindEmptyUser();
		if (NULL == p_User)
		{
			printf("Max Client!!\n");

			LeaveUser(c);

			SendMaxClient(c);

			return 0;
		}
		else
		{
			p_User->s = c;
			g_Room[ROOM_NUMBER].userCount++;
		}
	}

	// 방번호에서 몇번째 아인지 알 수 있다.
	int num = FindUser(c);
	printf("num : %d\n", num);

	while (1)
	{
		S_H h;

		re = recvn(c, (char*)&h, sizeof(h), 0);
		if (re <= 0)
		{
			printf("Client Close!!\n");			

			LeaveUser(c);

			break;
		}

		// 마우스 좌표를 보내준다.
		SendMousePOS(c);

		///////////////////////////////

		int count = 0;

		for (int i = 0; i<MAX_USER; i++)
		{
			if (true == g_Users[ROOM_NUMBER][i].isUsing)
			{
				count++;
			}
		}

		//printf("UserCount : %d \n\n", count);

		/////////////

		switch (h.cmd)
		{
		case CMD_CS_LOGIN:
			printf("Login Request!!\n");

			//SendLogin();
			break;
		case CMD_CS_GAMEMAP:
			SendRGAMEMAP(c, &m_Game);

			break;
		case CMD_CS_DATA:
			printf("CMD_CS_DATA!!\n");
			SendRDATA(c);

			break;
		case CMD_CS_MOUSEPOS:
			RecvnMousePOS(c);

			break;

		case CMD_CS_START:
			if (0 == OnRoomPlay(c, h.len))
			{
				printf("방 초기화 성공\n");
			}
			else
			{
				printf("방 초기화 실패\n");
			}
			SendRStart(c);

			break;
		default:
			printf("Unknown Command!!\n");
			break;
		}
	}

	return 0;
}

int main()
{	
	WSAData wsa;

	IniServer(&wsa);

	IniTCPServerMEx(2016, RunGame);

	EndServer();

	return 0;
}

int SendMaxClient(SOCKET c)
{
	S_H h;

	h.cmd = CMD_SC_MAXUSER;
	h.len = 0;

	char buf[1024];

	memcpy(buf, &h, sizeof(h));

	send(c, buf, sizeof(h), 0);

	return 0;
}

void LeaveUser(SOCKET c)
{
	for (int i = 0; i<MAX_USER; i++)
	{
		if (c == g_Users[ROOM_NUMBER][i].s)
		{
			g_Users[ROOM_NUMBER][i].isUsing = false;

			g_Room[ROOM_NUMBER].userCount--;
			if (0 == g_Room[ROOM_NUMBER].userCount)
			{
				g_Room[ROOM_NUMBER].isPlay = false;
			}
		}
	}
}

int SendMousePOS(SOCKET c)
{
	// 방이 게임 시작 되어 있지 않으면 노플레이
	if (false == g_Room[ROOM_NUMBER].isPlay)
	{
		return 0;
	}

	// 그 방에 유저수를 세어서 유저수만큼 MousePos가 안오면 안보냄
	/*int UserCount = 0;

	for (int i = 0; i<4; i++)
	{
		if (true == g_Users[ROOM_NUMBER][i].isUsing)
		{
			UserCount++;
		}
	}*/

	for (int i = 0; i<g_Room[ROOM_NUMBER].userCount; i++)
	{
		if (-1 == s_MousePOS[i].num)
		{
			return 0;
		}
	}

	////////////////////////////

	S_H h;
	S_RMOUSEPOS sdata;

	int hlen = sizeof(h);
	int dlen = sizeof(sdata);

	h.cmd = CMD_SC_RMOUSEPOS;
	h.len = dlen;

	for (int j = 0; j < 4; j++)
	{
		sdata.pos[j] = s_MousePOS[j];
	}

	char buf[1024];

	memcpy(buf, &h, hlen);
	memcpy(buf + hlen, &sdata, dlen);

	for (int i = 0; i<g_Room[ROOM_NUMBER].userCount; i++)
	{
		if (true == g_Users[ROOM_NUMBER][i].isUsing)
		{
			send(g_Users[ROOM_NUMBER][i].s, buf, hlen + dlen, 0);
		}
	}

	EnterCriticalSection(&g_Cs);

	IniMousePOS();

	LeaveCriticalSection(&g_Cs);

	return 0;
}

int RecvnMousePOS(SOCKET c)
{
	int re = 0;

	S_POS rdata;
	re = recvn(c, (char*)&rdata, sizeof(rdata), 0);
	if (re < 0)
	{
		printf("데이터가 제대로 오지 않음\n");

		return 0;
	}

	////////////////////////////////////////////////

	EnterCriticalSection(&g_Cs);

	s_MousePOS[rdata.num] = rdata;

	LeaveCriticalSection(&g_Cs);

	////////////////////////////////////////////////

	return 0;
}

int SendRStart(SOCKET c)
{
	S_H h;

	h.cmd = CMD_SC_RSTART;
	h.len = 0;

	char buf[1024];

	memcpy(buf, &h, sizeof(h));

	for (int i = 0; i<MAX_USER; i++)
	{
		if (true == g_Users[ROOM_NUMBER][i].isUsing)
		{
			send(g_Users[ROOM_NUMBER][i].s, buf, sizeof(h), 0);
		}
	}


	return 0;
}

void IniMousePOS()
{
	for(int i=0;i<4;i++)
	{
		s_MousePOS[i].num = -1;
		s_MousePOS[i].x = 0;
		s_MousePOS[i].y = 0;
	}
}

void IniServer(WSAData* wsa)
{
	WSAStartup(MAKEWORD(2, 2), wsa);

	for(int j=0;j<MAX_ROOM;j++)
	{
		for(int i=0;i<MAX_USER;i++)
		{
			g_Users[j][i].isUsing = false;
			g_Users[j][i].m_Combo = 0;
			g_Users[j][i].m_Score = 0;
		}
	}

	IniMousePOS();

	for (int i = 0; i<MAX_ROOM; i++)
	{
		g_Room[i].isPlay = false;
	}

	InitializeCriticalSection(&g_Cs);
}

void EndServer()
{
	DeleteCriticalSection(&g_Cs);

	WSACleanup();
}

int OnRoomPlay(SOCKET c, int num)
{
	for (int i=0;i<MAX_ROOM;i++)
	{
		if (g_Users[i][num].s == c)
		{
			g_Room[i].isPlay = true;

			return 0;
		}
	}

	return -1;
}

int FindUser(SOCKET c)
{
	for(int i=0;i<MAX_USER;i++)
	{
		if(c == g_Users[ROOM_NUMBER][i].s)
		{
			return i;
		}
	}

	return -1;
}

S_USER* FindEmptyUser()
{
	S_USER* pUser = NULL;

	EnterCriticalSection(&g_Cs);

	for(int i=0;i<MAX_USER;i++)
	{
		if(false == g_Users[ROOM_NUMBER][i].isUsing)
		{
			pUser = &g_Users[ROOM_NUMBER][i];

			pUser->isUsing = true;

			break;
		}
	}
	
	LeaveCriticalSection(&g_Cs);

	return pUser;
}

void DrawMapState(int (*t_Map)[MAP_SIZE], int re, int size)
{
	/*
		 GOAL        20
		 NO_WAY      21
		 GAME_END    22

		 SAME_CLICK  30
		 NOT_SAME    31
	*/

	for(int i=0;i<MAP_SIZE;i++)
	{
		for(int j=0;j<MAP_SIZE;j++)
		{
			printf("%d ",t_Map[i][j]);
		}
		printf("\n");
	}

	if(GOAL == re)
	{
		printf("RESULT = GOAL, size = %d\n", size);
	}
	else if(NO_WAY == re)
	{
		printf("RESULT = NO_WAY, size = %d\n", size);
	}
	else if(GAME_END == re)
	{
		printf("RESULT = GAME_END, size = %d\n", size);
	}
	else if(SAME_CLICK == re)
	{
		printf("RESULT = SAME_CLICK, size = %d\n", size);
	}
	else if(NOT_SAME == re)
	{
		printf("RESULT = NOT_SAME, size = %d\n", size);
	}

	printf("\n\n");
}

int SendRGAMEMAP(SOCKET c, KGame* Game)
{
	int num = FindUser(c);
	//printf("num : %d\n", num);

	S_H h;
	S_RGAMEMAP sdata;

	int hlen = sizeof(h);
	int dlen = sizeof(sdata);

	h.cmd = CMD_SC_RGAMEMAP;
	h.len = dlen;

	memcpy(sdata.map, (*Game).m_Map, sizeof(sdata.map));
	sdata.num = num;

	char buf[1024];

	memcpy(buf, &h, hlen);
	memcpy(buf+hlen, &sdata, dlen);

	send(c, buf, hlen + dlen, 0);	

	return 0;
}

int SendCollsion(SOCKET s)
{
	S_H h;
	
	h.cmd = CMD_SC_COLLISION;
	h.len = 0;

	char buf[1024];

	memcpy(buf, &h, sizeof(h));

	send(s, buf, sizeof(h), 0);
	
	return 0;
}

int SendRDATA(SOCKET s)
{
	int re = 0;	

	S_DATA rdata;
			
	re = recvn(s, (char*)&rdata, sizeof(rdata), 0);
	if(re < 0)
	{
		printf("데이터가 제대로 오지 않음\n");

		return 0;
	}

	KGame m_Game(ROOM_NUMBER);

	if (0 == m_Game.m_Map[rdata.sy][rdata.sx] || 0 == m_Game.m_Map[rdata.dy][rdata.dx])
	{
		printf("충돌 발생!! 애석!!\n");
		SendCollsion(s);

		return 0;
	}

	re = m_Game.RunGame(rdata.sx, rdata.sy, rdata.dx, rdata.dy);
	int tmp = m_Game.m_vPos.size();

	S_USER* t_User = NULL;

	if(GOAL == re || GAME_END == re)
	{
		EnterCriticalSection(&g_Cs);

		m_Game.m_Map[rdata.sy][rdata.sx] = 0;
		m_Game.m_Map[rdata.dy][rdata.dx] = 0;

		LeaveCriticalSection(&g_Cs);

		if(0 == m_Game.CheckGameOver())
		{
			re = GAME_END;
		}

		for(int i=0;i<MAX_USER;i++)
		{
			if(true == g_Users[ROOM_NUMBER][i].isUsing && s != g_Users[ROOM_NUMBER][i].s)
			{	
				S_H h;
				S_RADATA sdata;
				
				int hlen = sizeof(h);
				int dlen = sizeof(sdata);

				sdata.sx = rdata.sx;
				sdata.sy = rdata.sy;
				sdata.dx = rdata.dx;
				sdata.dy = rdata.dy;

				h.cmd = CMD_SC_RADATA;
				h.len = dlen;

				//////////////////////// find				
				
				t_User = FindPUser(g_Users[ROOM_NUMBER][i].s);

				sdata.re = re;
				
				sdata.combo = t_User->m_Combo;
				sdata.score = t_User->m_Score;
				
				ZeroMemory(sdata.pos, sizeof(sdata.pos));

				for(int j=tmp-1;0 <= j;j--)
				{
					sdata.pos[j].x = m_Game.m_vPos[j].x;
					sdata.pos[j].y = m_Game.m_vPos[j].y;
					sdata.pos[j].num = m_Game.m_vPos[j].num;
				}

				char buf[1024];

				memcpy(buf, &h, hlen);
				memcpy(buf+hlen, &sdata, dlen);

				send(g_Users[ROOM_NUMBER][i].s, buf, hlen+dlen, 0);
			}
		}
	}	
	
	S_H h;
	S_RDATA sdata;
		
	int hlen = sizeof(h);
	int dlen = sizeof(sdata);

	h.cmd = CMD_SC_RDATA;
	h.len = dlen;

	sdata.re = re;

	t_User = FindPUser(s);
	if (GOAL == sdata.re)
	{
		t_User->m_Score += 50 + (t_User->m_Combo * 100);

		t_User->m_Combo++;		
	}
	else
	{
		t_User->m_Combo = 0;
	}	

	sdata.combo = t_User->m_Combo;
	sdata.score = t_User->m_Score;	

	ZeroMemory(sdata.pos, sizeof(sdata.pos));

	for(int i=tmp-1;0 <= i;i--)
	{
		sdata.pos[i].x = m_Game.m_vPos[i].x;
		sdata.pos[i].y = m_Game.m_vPos[i].y;
		sdata.pos[i].num = m_Game.m_vPos[i].num;
	}

	char buf[1024];

	memcpy(buf, &h, hlen);
	memcpy(buf+hlen, &sdata, dlen);

	send(s, buf, hlen+dlen, 0);	

	DrawMapState(m_Game.m_Map, re, tmp);

	return 0;
}