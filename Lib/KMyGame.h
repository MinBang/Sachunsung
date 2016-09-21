
typedef struct _POS
{
	int x, y;
	int num;
}S_POS;

typedef struct _ONCLICK
{
	int x,y;

	bool isUsing;
}S_ONCLICK;

// �迭 �ε��� ������
#define SOUR         0
#define DEST         1

// ���� ����
#define UP          10
#define DOWN        11
#define	LEFT        12
#define RIGHT       13

// ��� ����

#define GOAL        20
#define NO_WAY      21
#define GAME_END    22
#define SAME_CLICK  23
#define NOT_SAME    24

// ī�� ����

#define CARD_COUNT   8
#define CARD_WIDTH  40
#define CARD_HEIGHT 40

// �� ����

#define MAP_SIZE    15
#define MAP_STARTX  150
#define MAP_STARTY  150

// �������� ����

#define WAIT         0
#define GAMING       1
#define END          2