
// DrivingDemo.h : DrivingDemo Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CDrivingDemoApp:
// �йش����ʵ�֣������ DrivingDemo.cpp
//

class CDrivingDemoApp : public CWinApp
{
public:
	CDrivingDemoApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

};

extern CDrivingDemoApp theApp;
