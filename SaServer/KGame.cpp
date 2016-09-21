#include "StdAfx.h"
#include "KGame.h"
#include <time.h>

#define MAX_ROOM 10

int g_Map[MAX_ROOM][MAP_SIZE][MAP_SIZE] = { 0, };

////////////////////////////////////////

int g_Map1[MAP_SIZE][MAP_SIZE] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0 },
	{ 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0 },
	{ 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0 },
	{ 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0 },
	{ 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0 },
	{ 0, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 0 },
	{ 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0 },
	{ 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0 },
	{ 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0 },
	{ 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0 },
	{ 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0 },
	{ 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

int g_Map2[MAP_SIZE][MAP_SIZE] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0 },
	{ 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0 },
	{ 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0 },
	{ 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0 },
	{ 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0 },
	{ 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0 },
	{ 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0 },
	{ 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0 },
	{ 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

int g_Map3[MAP_SIZE][MAP_SIZE] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

int g_Map10[MAP_SIZE][MAP_SIZE] = {
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

////////////////////////////////////////

KGame::KGame(void)
{
	m_Score = 0;
	m_Index = 0;
	m_Combo = 0;
	m_Flow = 0;

	m_Map = g_Map[m_Index];
}

KGame::KGame(int index)
{
	m_Index = index;
	m_Score = 0;
	m_Combo = 0;
	m_Flow = 0;

	m_Map = g_Map[m_Index];	
}

KGame::~KGame(void)
{
}

int KGame::IniMap()
{
	srand(time(NULL));

	int num = rand() % 10;

	switch (num)
	{
	case 0:
		break;
	default:
		memcpy(&g_Map[m_Index], g_Map1, sizeof(g_Map2));

		break;
	}

	return 0;
}


int KGame::MakeMap(void)
{
	srand(time(NULL));

	m_Map = g_Map[m_Index];

	int datum;
	int count[CARD_COUNT];

	// ��� ���� ���ϱ�

	int maxLen = MAP_SIZE-2;
	int maxCount = 0;
	int countSum = 0;

	for(int i=0;i<MAP_SIZE;i++)
	{
		for(int j=0;j<MAP_SIZE;j++)
		{
			if(9 == m_Map[i][j])
			{
				maxCount++;
			}
		}
	}

	if(64 <= maxCount)
	{
		datum = (int)(maxCount/2) / CARD_COUNT;

		for(int i=0;i<CARD_COUNT;i++)
		{
			count[i] = datum;
		}	

		for(int i=0;i<(CARD_COUNT-1);i++)
		{
			int num = 0;

			if(32 <= datum)
			{
				num = rand()%5 - 2;
			}
			else
			{
				num = rand()%3 - 1;
			}
			

			count[i] += num;
			countSum += count[i];

		}
		count[CARD_COUNT-1] = (maxCount/2) - countSum;

			}
	else
	{
		datum = maxCount/2;
		for(int i=0;i<CARD_COUNT;i++)
		{
			count[i] = 0;
		}

		while(0 < datum)
		{
			int num = rand()%8;

			count[num]++;
			datum--;
		}
	}

	////////////////////////////////////

	int halfCount = maxCount/2;
	int flag = 0;

	// ������ ���� �������� �׸���
	for(int i=0;i<MAP_SIZE;i++)
	{
		for(int j=0;j<MAP_SIZE;j++)
		{
			if(9 == m_Map[i][j])
			{
				int num = rand()%CARD_COUNT;

				if(0 < count[num])
				{
					m_Map[i][j] = num+1;
					count[num] --;

					halfCount--;

					if(halfCount < (halfCount/5)*2)
					{
						for(int y=MAP_SIZE-1;0<y;y--)
						{
							for(int x=MAP_SIZE-1;0<x;x--)
							{
								if(9 == m_Map[y][x])
								{
									m_Map[y][x] = num+1;
									flag = 1;

									break;
								}
							}

							if(1 == flag)
							{
								flag = 0;
								break;
							}
						}
					}
					else
					{
						while(1)
						{
							int yNum = rand()%(MAP_SIZE-2)+1;
							int xNum = rand()%(MAP_SIZE-2)+1;

							if(m_Map[yNum][xNum] == 9)
							{
								m_Map[yNum][xNum] = num+1;
								break;
							}
						}		
					}								
				}
				else
				{
					j--;
				}
			}
		}
	}

	return 0;
}

int KGame::RunGame(int sx, int sy, int dx, int dy)
{
	printf("POS : %d,%d  %d,%d\n", sx, sy, dx, dy);
	printf("VALUE : %d %d\n",m_Map[sy][sx], m_Map[dy][dx]);

	if(sx == dx && sy == dy)
	{
		return SAME_CLICK;
	}

	if(m_Map[sy][sx] != m_Map[dy][dx])
	{
		return NOT_SAME;
	}

	int re = CanGoal(sx, sy, dx, dy);
	
	if(GOAL == re)
	{
		m_Score += 50 + (m_Combo * 100);

		m_Combo++;
	}	
	
	return re;
}

int KGame::CanGoal(int sx, int sy, int dx, int dy)
{	
	int re = NO_WAY; //���ϰ�

	KNode* std_Node; // �������� ����Ű�� ������
	KNode* p_Node;	// �۾��� �̷����� ���� ����Ű�� ������	
	KNode s_Node;   // ���� ���۳��
	s_Node.InitNode(sx, sy, 0, 1, dx, dy);
	m_Node.InitNode(sx, sx, 0, 0, dx, dy);

	m_Node.vNodes.push_back(s_Node);
	std_Node = &m_Node;

	while(NULL != std_Node)
	{
		//������ ����� �Ǿ��� �ƴ� �ǵں��� �켱������ ���������� ���ĵǾ��ֱ⿡ �ǵں��� �����Ѵ�.
		for(int i=std_Node->vNodes.size()-1;-1<i;i--)
		{			
			p_Node = &std_Node->vNodes[i]; //�۾��� ����� �Ǵ� ��

			int xpos = p_Node->GetXPos();
			int ypos = p_Node->GetYPos();

			//���� ���� �۾��ϰ� �ִ� �������� ��ġ�� ��ǥ��ġ�̰� ����Ƚ���� 4�� �����ϰ�� GOAL!!
			if(xpos == dx && ypos == dy && p_Node->GetDirCount() != 4)
			{
				int size = m_vPos.size();

				re = GOAL;

				if(0 == size)
				{
					GoalTrace(p_Node);
				}
				else
				{
					if(p_Node->GetNum() < size)
					{
						GoalTrace(p_Node);	
					}
				}

				std_Node = NonExistAddNode(p_Node);				
				continue;
			}

			p_Node = AddNextNode(p_Node, dx, dy);
			
			//�߰��� ��尡 0�� �ϰ�� �ڽĳ�尡 2�� �̻��� ������ �Ž��� �ö󰡼� ���й��� ����.
			if(0 == p_Node->vNodes.size())
			{
				std_Node = NonExistAddNode(p_Node);
				break;
			}
			//�߰� ��尡 1���̻��� ��� �����Ѵ�. �ǵڳ�尡 �����켱�������.
			else
			{
				ArrangeAddNode(p_Node);

				std_Node = p_Node;
				break;
			}
		}
	}
	
	m_Flow = m_vPos.size();

	//��� ��� �޸� ����.
	m_Node.vNodes.clear();

	return re;
}

KNode* KGame::AddNextNode(KNode* p_Node, int dx, int dy)
{
	int xpos = p_Node->GetXPos();
	int ypos = p_Node->GetYPos();
	int dircount = 0; //������ ���̴� Ƚ���� �����ϱ� ���� ����

	//���� �۾��ϴ� ģ���� 4�� ���ϸ�
	if(p_Node->GetDirCount() < 4)
	{				
		// DOWN
		if((0 == m_Map[ypos+1][xpos] || (ypos+1 == dy && xpos == dx)) && ypos+1 < MAP_SIZE && UP != p_Node->GetDir())
		{	
			KNode t_Node;					
			t_Node.InitNode(xpos, ypos+1, DOWN, p_Node->GetNum()+1, dx, dy);
			t_Node.preNode = p_Node;

			if(DOWN != p_Node->GetDir())
			{
				dircount = p_Node->GetDirCount()+1;
				t_Node.SetDirCount(dircount);
			}
			else
			{
				dircount = p_Node->GetDirCount();
				t_Node.SetDirCount(dircount);
			}

			p_Node->vNodes.push_back(t_Node);	

		}
		// UP
		if((0 == m_Map[ypos-1][xpos] || (ypos-1 == dy && xpos == dx)) && 0 <= ypos-1 && DOWN != p_Node->GetDir())
		{
			KNode t_Node;					
			t_Node.InitNode(xpos, ypos-1, UP, p_Node->GetNum()+1, dx, dy);
			t_Node.preNode = p_Node;

			if(UP != p_Node->GetDir())
			{
				dircount = p_Node->GetDirCount()+1;
				t_Node.SetDirCount(dircount);
			}
			else
			{
				dircount = p_Node->GetDirCount();
				t_Node.SetDirCount(dircount);
			}

			p_Node->vNodes.push_back(t_Node);
	
		}

		//RIGHT
		if((0 == m_Map[ypos][xpos+1] || (ypos == dy && xpos+1 == dx)) && xpos+1 < MAP_SIZE && LEFT != p_Node->GetDir())
		{
			KNode t_Node;
			t_Node.InitNode(xpos+1, ypos, RIGHT, p_Node->GetNum()+1, dx, dy);
			t_Node.preNode = p_Node;

			if(RIGHT != p_Node->GetDir())
			{
				dircount = p_Node->GetDirCount()+1;
				t_Node.SetDirCount(dircount);
			}
			else
			{
				dircount = p_Node->GetDirCount();
				t_Node.SetDirCount(dircount);
			}

			p_Node->vNodes.push_back(t_Node);
										
		}

		//LEFT
		if((0 == m_Map[ypos][xpos-1] || (ypos == dy && xpos-1 == dx)) && 0 <= xpos-1 && RIGHT != p_Node->GetDir())
		{
			KNode t_Node;
			t_Node.InitNode(xpos-1, ypos, LEFT, p_Node->GetNum()+1, dx, dy);
			t_Node.preNode = p_Node;

			if(LEFT != p_Node->GetDir())
			{
				dircount = p_Node->GetDirCount()+1;
				t_Node.SetDirCount(dircount);
			}
			else
			{
				dircount = p_Node->GetDirCount();
				t_Node.SetDirCount(dircount);
			}

			p_Node->vNodes.push_back(t_Node);
		}
	}
	//4�� �̻��̸� 2�� ���� �������� ���ư��� ����Ž���κ� ����
	else 
	{
		p_Node = ReTwoCourse(p_Node);
	}

	return p_Node;
}

KNode* KGame::NonExistAddNode(KNode* p_Node)
{
	KNode* t_Node = p_Node->preNode;

	while(NULL != t_Node && t_Node->vNodes.size() < 2)
	{
		t_Node->vNodes.pop_back();
		t_Node = t_Node->preNode;
	}

	if(NULL != t_Node)
	{
		t_Node->vNodes.pop_back();
	}

	return t_Node;
}

int KGame::ArrangeAddNode(KNode* p_Node)
{
	int size = p_Node->vNodes.size();		

	for(int i=1;i<size;i++)
	{
		for(int j=0;j<size-i;j++)
		{
			if(p_Node->vNodes[j].GetPrior() < p_Node->vNodes[j+1].GetPrior())
			{
				KNode t_Node = p_Node->vNodes[j];
				p_Node->vNodes[j] = p_Node->vNodes[j+1];
				p_Node->vNodes[j+1] = t_Node;
			}
		}
	}

	return 0;
}

int KGame::SeletedObject(int x, int y)
{
	return m_Map[y][x];
}

void KGame::IniCombo(void)
{
	m_Combo = 0;
}

int KGame::GoalTrace(KNode* p_Node)
{
	m_vPos.clear();

	KNode* t_Node = p_Node;

	while(t_Node != NULL)
	{
		S_POS t_Pos;
		t_Pos.x = t_Node->GetXPos();
		t_Pos.y = t_Node->GetYPos();
		t_Pos.num = t_Node->GetNum();

		m_vPos.push_back(t_Pos);

		t_Node = t_Node->preNode;
	}

	return 0;
}

KNode* KGame::ReTwoCourse(KNode* p_Node)
{
	KNode* t_Node = p_Node->preNode;

	while(1)
	{
		t_Node = t_Node->preNode;
		if(2 == t_Node->GetDirCount())
		{
			break;
		}

		t_Node->vNodes.clear();
	}

	t_Node->vNodes.pop_back();

	return t_Node;
}

int KGame::CheckGameOver(void)
{
	for(int i=0;i<MAP_SIZE;i++)
	{
		for(int j=0;j<MAP_SIZE;j++)
		{
			if(0 != m_Map[i][j])
			{
				return 1;
			}
		}
	}

	return 0;
}

void KGame::IniGame(int level)
{
	m_Score = 0;
	m_Combo = 0;
	m_Flow = 0;
	m_vPos.clear();
}


