#pragma once
#include <vector>

using namespace std;

class KNode
{
public:
	KNode(void);
	~KNode(void);

private:
	// 노드 내용
	int x, y;
	int prior;
	int num;	
	int dir;
	int dircount;

	int onPrior(int dx, int dy);
	//노드 링크
public:
	KNode* preNode;
	vector<KNode> vNodes;
public:
	//static KNode* CreateNode(int _x, int _y, int _dir, int _num, int dx, int dy);	
	void InitNode(int _x, int _y, int _dir, int _num, int dx, int dy);
	int GetXPos(void);
	int GetYPos(void);
	int GetDir(void);
	int GetDirCount(void);
	int SetDirCount(int _dircount);
	int GetPrior();
	int GetNum(void);
};
