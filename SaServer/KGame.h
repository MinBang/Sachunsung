#pragma once
#include "KNode.h"
#include "../Lib/NetSaChunSung.h"

class KGame
{
public:
	KGame(void);
	KGame::KGame(int index);
	~KGame(void);

private:		
	int m_Flow;
	int m_Index;
	KNode m_Node;

	int CanGoal(int sx, int sy, int dx, int dy);	
	KNode* AddNextNode(KNode* p_Node, int dx, int dy);
	KNode* NonExistAddNode(KNode* p_Node);
	int ArrangeAddNode(KNode* p_Node);		
	void IniCombo(void);	
	int GoalTrace(KNode* p_Node);
	KNode* ReTwoCourse(KNode* p_Node);	
	void IniGame(int level);
	int SeletedObject(int x, int y);	

public:
		
	int m_Score;
	int m_Combo;
	int(*m_Map)[MAP_SIZE];
	vector<S_POS>m_vPos;

	int RunGame(int sx, int sy, int dx, int dy);
	int CheckGameOver(void);
	int IniMap();
	int MakeMap(void);
};
