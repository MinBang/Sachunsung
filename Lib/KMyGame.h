
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

// 배열 인덱스 재정의
#define SOUR         0
#define DEST         1

// 방향 정의
#define UP          10
#define DOWN        11
#define	LEFT        12
#define RIGHT       13

// 결과 정의

#define GOAL        20
#define NO_WAY      21
#define GAME_END    22
#define SAME_CLICK  23
#define NOT_SAME    24

// 카드 정의

#define CARD_COUNT   8
#define CARD_WIDTH  40
#define CARD_HEIGHT 40

// 맵 정의

#define MAP_SIZE    15
#define MAP_STARTX  150
#define MAP_STARTY  150

// 스테이지 정의

#define WAIT         0
#define GAMING       1
#define END          2