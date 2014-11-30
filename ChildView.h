
// ChildView.h : CChildView 类的接口
//


#pragma once

#include "Wheel.h"
#include "Car.h"
// CChildView 窗口

class CChildView : public CWnd
{
// 构造
public:
	CChildView();

// 特性
public:

// 操作
public:

// 重写
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	BOOL PreTranslateMessage(MSG* pMsg); 
// 实现
public:
	virtual ~CChildView();
	 
	// 生成的消息映射函数
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

	
	Car* m_car;
	
public:
	afx_msg void OnItemGuideLine();
	void OnUpdateImprove(CCmdUI *pCmdUI);
};

