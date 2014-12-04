
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
	
	BOOL OnEraseBkgnd(CDC* pDC);
	void OnMenuItemRadius(CCmdUI *pCmdUI);
	void OnMenuItemOutsideFrontCar(CCmdUI *pCmdUI);
	void OnMenuItemOutsideFrontWheel(CCmdUI *pCmdUI);
	void OnMenuItemOutsideRearWheel(CCmdUI *pCmdUI);
	void OnMenuItemInsideFrontWheel(CCmdUI *pCmdUI);
	afx_msg void OnItemRightTurn();
	afx_msg void OnItemFree();
	afx_msg void OnAppExit();

	afx_msg void OnMenuItemRadius();
	afx_msg void OnMenuItemOutsideFrontCar();
	afx_msg void OnMenuItemOutsideFrontWheel();
	afx_msg void OnMenuItemOutsideRearWheel();
	afx_msg void OnItemReverseParking();
	afx_msg void OnItemSideParking();
	afx_msg void OnMenuItemInsideFrontWheel();
};

