
// SaClient.h : SaClient ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CSaClientApp:
// �� Ŭ������ ������ ���ؼ��� SaClient.cpp�� �����Ͻʽÿ�.
//

class CSaClientApp : public CWinApp
{
public:
	CSaClientApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSaClientApp theApp;
