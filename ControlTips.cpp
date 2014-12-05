#include "StdAfx.h"
#include "ControlTips.h"


ControlTips::ControlTips(void)
{
	Util::LOG(L"ControlTips");
	m_location = new ThreeDPoint;
	m_location->z = 0;
	m_speed = 1;
}


ControlTips::~ControlTips(void)
{
	Util::LOG(L"~ControlTips");
	if(m_location!=NULL)
	delete m_location;
	m_location = NULL;
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
	CFont font, *pOldFont= NULL;//�������������ָ�� ������Ը�������ѡ����Ҫ���������ͺʹ�С
    font.CreatePointFont(180, L"����", &dc);
	pOldFont = dc.SelectObject(&font);
	dc.TextOutW(this->m_dX,this->m_dY,L"����˵��:");
	dc.TextOutW(this->m_dX,this->m_dY+50,L"ǰ��:�� ����:��");
	dc.TextOutW(this->m_dX,this->m_dY+100,L"��ת:�� ��ת:��");
	CString tmp;
	tmp.Format(L"����/����:HOME/END   ��ǰ�ٶ�:%d",m_speed);
	dc.TextOutW(this->m_dX,this->m_dY+150,tmp);
	dc.SelectObject(pOldFont);
	font.DeleteObject();
}
