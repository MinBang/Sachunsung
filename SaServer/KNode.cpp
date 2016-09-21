#include "StdAfx.h"
#include "KNode.h"

KNode::KNode(void)
{
}

KNode::~KNode(void)
{
}

void KNode::InitNode(int _x, int _y, int _dir ,int _num, int dx, int dy)
{
	preNode = NULL;
	x = _x;
	y = _y;
	dir = _dir;
	dircount = 0;
	num = _num;
	prior = onPrior(dx, dy);
}

int KNode::onPrior(int dx, int dy)
{
	int xpri = 0;
	int ypri = 0;

	if(x < dx)
	{
		xpri = dx - x;
	}
	else
	{
		xpri = x - dx;
	}

	if(y < dy)
	{
		ypri = dy - y;
	}
	else
	{
		ypri = y - dy;
	}
	
	return (xpri + ypri);
}

int KNode::GetXPos(void)
{
	return x;
}

int KNode::GetYPos(void)
{
	return y;
}

int KNode::GetDir(void)
{
	return dir;
}

int KNode::GetDirCount(void)
{
	return dircount;
}

int KNode::SetDirCount(int _dircount)
{
	dircount = _dircount;

	return 0;
}

int KNode::GetPrior(void)
{
	return prior;
}

int KNode::GetNum(void)
{
	return num;
}
