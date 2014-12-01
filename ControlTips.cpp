#include "StdAfx.h"
#include "ControlTips.h"


ControlTips::ControlTips(void)
{
	m_location = new ThreeDPoint;
	m_location->z = 0;
}


ControlTips::~ControlTips(void)
{
	if(m_location!=NULL)
	delete m_location;
}
void ControlTips::setParams(double x,double y)
{
	this->m_dX = x;
	this->m_dY = y;
	m_location->x = x;
	m_location->y = y;
}

void ControlTips:: Translate(double x,double y,double z)
{
	MathUtil::Translate(m_location,1,x,y,z);
	this->m_dX = m_location->x;
	this->m_dY = m_location->y;
}
void ControlTips:: Scale(double ratio)
{
	Scale(ratio,this->m_dX,this->m_dY, 0);
}
void ControlTips:: Scale(double ratio,double x,double y,double z)
{
	MathUtil::Translate(m_location,1,-x,-y,0);
	MathUtil::Scale(m_location,1,ratio);
	MathUtil::Translate(m_location,1,x,y,0);
}
void ControlTips:: Rotate(double degree)
{
	Rotate(degree,this->m_dX,this->m_dY,0);
}
void ControlTips:: Rotate(double degree,double x,double y,double z)
{
	MathUtil::Translate(m_location,1,-x,-y,0);
	MathUtil::RotateZ(m_location,1,degree);
	MathUtil::Translate(m_location,1,x,y,0);
}
void ControlTips:: draw(CDC &dc)
{
	CFont font, *pOldFont= NULL;//定义字体对象及其指针 ，你可以根据需求选择你要的字体类型和大小
    font.CreatePointFont(180, L"楷体", &dc);
	pOldFont = dc.SelectObject(&font);
	dc.TextOutW(this->m_dX,this->m_dY,L"操作说明:");
	dc.TextOutW(this->m_dX,this->m_dY+50,L"前进:↑ 后退:↓");
	dc.TextOutW(this->m_dX,this->m_dY+100,L"左转:← 右转:→");
	dc.SelectObject(pOldFont);
	font.DeleteObject();
}
