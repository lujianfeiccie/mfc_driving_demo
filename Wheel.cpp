#include "StdAfx.h"
#include "Wheel.h"
#include "Util.h"
#define SIZE_OF_POINT 3
Wheel::Wheel()
{
	pt = new CPoint[SIZE_OF_POINT];
	pt3d = new ThreeDPoint[SIZE_OF_POINT];

	//setParams(x,y,100);
}
void Wheel::setParams(int x,int y,double car_cx,double car_cy,double ratio,double m_fWheel_diameter)
{
	this->m_dX = x;
	this->m_dY = y;
	this->m_fWheel_diameter = m_fWheel_diameter;
	this->m_car_cx = car_cx;
	this->m_car_cy = car_cy;
	this->m_dRatio = ratio;
	this->m_degree = 0;
	for(int i=0;i<SIZE_OF_POINT;i++) (pt3d+i)->z = 0;

	(pt3d+0)->x = x;(pt3d+0)->y = y-m_fWheel_diameter/2.0;

	(pt3d+1)->x = x;(pt3d+1)->y = y;

	(pt3d+2)->x = x;(pt3d+2)->y = y+m_fWheel_diameter/2.0;

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
	 m_dX=(pt3d+1)->x;
	 m_dY=(pt3d+1)->y;
}
void Wheel::Scale(double ratio)
{
	MathUtil::Translate(pt3d,SIZE_OF_POINT,-m_dX,-m_dY,0);
	MathUtil::Scale(pt3d,SIZE_OF_POINT,ratio);
	MathUtil::Translate(pt3d,SIZE_OF_POINT, m_dX, m_dY,0);
}
void Wheel::ScaleCar(double ratio)
{
	MathUtil::Translate(pt3d,SIZE_OF_POINT,-m_car_cx,-m_car_cy,0);
	MathUtil::Scale(pt3d,SIZE_OF_POINT,ratio);
	MathUtil::Translate(pt3d,SIZE_OF_POINT, m_car_cx, m_car_cy,0);

	 m_dX=(pt3d+1)->x;
	 m_dY=(pt3d+1)->y;
	m_dRatio *= ratio;
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

	 m_dX=(pt3d+1)->x;
	 m_dY=(pt3d+1)->y;

	m_degree += degree;

	if(m_degree>359) m_degree = 0;

	if(m_degree<0) m_degree = 359;

}
 void Wheel::draw(CPaintDC &dc)
 {
	 for(int i=0;i<SIZE_OF_POINT;i++)
	 {
		(pt+i)->x = (pt3d+i)->x;
		(pt+i)->y = (pt3d+i)->y;
	 }
	dc.Polygon(pt,SIZE_OF_POINT);
 }

Wheel::~Wheel(void)
{
	delete []pt;
	delete []pt3d;
}