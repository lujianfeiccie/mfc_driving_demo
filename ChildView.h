
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
	IControl* m_space;
public:
	afx_msg void OnItemGuideLine();
	BOOL OnEraseBkgnd(CDC* pDC);
	void OnUpdateImprove(CCmdUI *pCmdUI);
	afx_msg void OnItemRightTurn();
	afx_msg void OnItemFree();
	afx_msg void OnAppExit();

};

