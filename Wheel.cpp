#include "StdAfx.h"
#include "Wheel.h"
#include "Util.h"
#define SIZE_OF_POINT 5
Wheel::Wheel()
{
	pt = new CPoint[SIZE_OF_POINT];
	pt3d = new ThreeDPoint[SIZE_OF_POINT];
	this->m_dRatio = 1;
}
void Wheel::setParams(int x,int y,double car_cx,double car_cy,double m_fWheel_diameter,double m_fWheel_width)
{
	this->m_dX = x;
	this->m_dY = y;
	this->m_fWheel_diameter = m_fWheel_diameter;
	this->m_car_cx = car_cx;
	this->m_car_cy = car_cy;
	this->m_degree = 0;
	this->m_fWheel_width = m_fWheel_width;
	for(int i=0;i<SIZE_OF_POINT;i++) (pt3d+i)->z = 0;

	(pt3d+4)->x = x;(pt3d+4)->y = y;//中心点

	(pt3d+0)->x = x-m_fWheel_width /2.0; (pt3d+0)->y = y-m_fWheel_diameter/2.0;//左上角
	(pt3d+1)->x = x+m_fWheel_width /2.0; (pt3d+1)->y = y-m_fWheel_diameter/2.0;//右上角
	(pt3d+2)->x = x+m_fWheel_width /2.0; (pt3d+2)->y = y+m_fWheel_diameter/2.0;//右下角
	(pt3d+3)->x = x-m_fWheel_width /2.0; (pt3d+3)->y = y+m_fWheel_diameter/2.0;//左下角

	this->m_car_cx = car_cx;
	this->m_car_cy = car_cy;	
}


void Wheel::go_foward()
{
//	Util::LOG(L"before (%lf,%lf)",pt3d->x,pt3d->y);
	MathUtil::Translate(pt3d,SIZE_OF_POINT,0,-1,0);
	
//	Util::LOG(L"before (%lf,%lf)",pt3d->x,pt3d->y);
}
void Wheel::go_backward()
{
	MathUtil::Translate(pt3d,SIZE_OF_POINT,0,1,0);
}
void Wheel::turn_left()
{
	Rotate(-1);
}
void Wheel::turn_right()
{
	Rotate(1);
}

void Wheel::Translate(double x,double y,double z)
{
	MathUtil::Translate(pt3d,SIZE_OF_POINT,x,y,z);
	 m_dX=(pt3d+4)->x;
	 m_dY=(pt3d+4)->y;
}
void Wheel::Scale(double ratio)
{
	Scale(ratio,m_dX,m_dY,0);
}
void Wheel::Scale(double ratio,double x,double y,double z)
{
	MathUtil::Translate(pt3d,SIZE_OF_POINT,-x,-y,z);
	MathUtil::Scale(pt3d,SIZE_OF_POINT,ratio);
	MathUtil::Translate(pt3d,SIZE_OF_POINT, x, y,z);
	m_dRatio *= ratio;
}
void Wheel::ScaleCar(double ratio)
{
	Scale(ratio, m_car_cx, m_car_cy,0);
	 m_dX=(pt3d+4)->x;
	 m_dY=(pt3d+4)->y;
}
void Wheel::Rotate(double degree)
{
	Rotate(degree,m_dX,m_dY,0);
}
void Wheel::Rotate(double degree,double x,double y,double z)
{
	MathUtil::Translate(pt3d,SIZE_OF_POINT,-x,-y,0);
	MathUtil::RotateZ(pt3d,SIZE_OF_POINT,degree);
	MathUtil::Translate(pt3d,SIZE_OF_POINT,x,y,0);

	 m_dX=(pt3d+4)->x;
	 m_dY=(pt3d+4)->y;

	m_degree += degree;

}
 void Wheel::draw(CDC &dc)
 {
	 for(int i=0;i<SIZE_OF_POINT;i++)
	 {
		(pt+i)->x = (pt3d+i)->x;
		(pt+i)->y = (pt3d+i)->y;
	 }
	CPen MyPen,*OldPen;	
	MyPen.CreatePen(PS_SOLID,1,RGB(0,0,0));
	OldPen=dc.SelectObject(&MyPen);	
	CBrush MyBrush,*OldBrush;	
	MyBrush.CreateSolidBrush(RGB(0,0,0));
	OldBrush=dc.SelectObject(&MyBrush);
	//绘制
	dc.Polygon(pt,SIZE_OF_POINT-1);

	dc.SelectObject(OldPen);
	dc.SelectObject(OldBrush);
 }

Wheel::~Wheel(void)
{
	delete []pt;
	delete []pt3d;
}