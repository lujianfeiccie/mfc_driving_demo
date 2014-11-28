#include "StdAfx.h"
#include "Wheel.h"
#include "Util.h"
#define SIZE_OF_POINT 2
Wheel::Wheel(int x,int y, double ratio)
{
	degree = 0;
	m_dRatio = ratio;
	pt = new CPoint[SIZE_OF_POINT];
	pt3d = new ThreeDPoint[SIZE_OF_POINT];

	//setParams(x,y,100);
}
void Wheel::setParams(int x,int y,double m_fWheel_diameter)
{
	this->m_dX = x;
	this->m_dY = y;
	this->m_fWheel_diameter = m_fWheel_diameter;

	for(int i=0;i<SIZE_OF_POINT;i++) (pt3d+i)->z = 0;

	(pt3d+0)->x = x;(pt3d+0)->y = y-m_fWheel_diameter/2.0;

	(pt3d+1)->x = x;(pt3d+1)->y = y+m_fWheel_diameter/2.0;

	Scale(m_dRatio);
}
Wheel::~Wheel(void)
{
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
	MathUtil::Translate(pt3d,SIZE_OF_POINT,-m_dX,-m_dY,0);
	MathUtil::RotateZ(pt3d,SIZE_OF_POINT,-1);
	MathUtil::Translate(pt3d,SIZE_OF_POINT,m_dX,m_dY,0);

	degree += -1;
	if(degree<0) degree = 359;
	Util::LOG(L"degree=%d",degree);
}
void Wheel::turn_right()
{
	MathUtil::Translate(pt3d,SIZE_OF_POINT,-m_dX,-m_dY,0);
	MathUtil::RotateZ(pt3d,SIZE_OF_POINT,1);
	MathUtil::Translate(pt3d,SIZE_OF_POINT,m_dX,m_dY,0);

	degree += 1;
	if(degree>359) degree = 0;
	Util::LOG(L"degree=%d",degree);
}

void Wheel::Translate(double x,double y,double z)
{
	MathUtil::Translate(pt3d,SIZE_OF_POINT,x,y,z);
}
void Wheel::Scale(double ratio)
{
	MathUtil::Translate(pt3d,SIZE_OF_POINT,-m_dX,-m_dY,0);
	MathUtil::Scale(pt3d,SIZE_OF_POINT,ratio);
	MathUtil::Translate(pt3d,SIZE_OF_POINT, m_dX, m_dY,0);
}
 void Wheel::draw(CPaintDC &dc)
 {
	 for(int i=0;i<SIZE_OF_POINT;i++)
	 {
		(pt+i)->x = pt3d[i].x;
		(pt+i)->y = pt3d[i].y;
	 }
	dc.Polygon(pt,SIZE_OF_POINT);
 }

