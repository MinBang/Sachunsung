#pragma once

// SaNet 명령 대상입니다.
#include "../Lib/NetSaChunSung.h"

class CSaClientView;

class SaNet : public CSocket
{
public:
	SaNet();
	virtual ~SaNet();

	CSaClientView* m_View;
	int SendData(int sx, int sy, int dx, int dy);
//	virtual void OnReceive(int nErrorCode);
	int RecvRGAMEMAP(void);
	int SendGAMEMAP(void);
	int SendMousePOS(S_POS t_Pos);
	int RecvRMOUSEPOS(void);
	int SendStart();
	int RecvRADATA();
	int RecvRDATA();
	virtual void OnReceive(int nErrorCode);
};


