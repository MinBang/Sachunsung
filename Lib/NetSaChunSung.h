#include <vector>
#include "KMyGame.h"

using namespace std;

//////////////////////////////

#define CMD_CS_LOGIN      100
#define CMD_SC_RLOGIN     101

#define CMD_CS_GAMEMAP    102
#define CMD_SC_RADATA     105

#define CMD_CS_DATA       103
#define CMD_SC_RDATA      104

#define CMD_CS_MOUSEPOS   106
#define CMD_SC_RMOUSEPOS  107

#define CMD_CS_START      108
#define CMD_SC_RSTART     109

#define CMD_SC_RGAMEMAP   110


// 예외처리
#define CMD_SC_MAXUSER     120
#define CMD_SC_COLLISION   121
#define CMD_SC_ALREADYPLAY 122

typedef struct _H
{
	int cmd;
	int len;
}S_H;

typedef struct _LOGIN
{
	char id[20];
	char passwd[20];
}S_LOGIN;

typedef struct _RLOGIN
{
	int re; //참가 가능 불가능
}S_RLOGIN;

typedef struct _RGAMESTART
{
	int map[MAP_SIZE][MAP_SIZE];
	int num;
}S_RGAMEMAP;

typedef struct _DATA
{
	int sx, sy;
	int dx, dy;
}S_DATA;

typedef struct _RDATA
{
	S_POS pos[46];

	int re;
	int score;
	int combo;
}S_RDATA;

typedef struct _RADATA
{
	S_POS pos[46];

	int sx, sy;
	int dx, dy;

	int re;
	int score;
	int combo;
}S_RADATA;

typedef struct _RMOUSEPOS
{
	S_POS pos[4];
}S_RMOUSEPOS;
