
// ChildView.h : CChildView ��Ľӿ�
//


#pragma once

#include "Wheel.h"
#include "Car.h"
// CChildView ����

class CChildView : public CWnd
{
// ����
public:
	CChildView();

// ����
public:

// ����
public:

// ��д
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	BOOL PreTranslateMessage(MSG* pMsg); 
// ʵ��
public:
	virtual ~CChildView();
	 
	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

	
	Car* m_car;
	
public:
	afx_msg void OnItemGuideLine();
	void OnUpdateImprove(CCmdUI *pCmdUI);
};

