#include "StdAfx.h"
#include "SpaceSideParking.h"
#define SIZE_OF_VERTEX 9

SpaceSideParking::SpaceSideParking(void)
{
	m_pt3d = new ThreeDPoint[SIZE_OF_VERTEX];
	m_pt = new CPoint[SIZE_OF_VERTEX];
	m_tips = new ControlTips;
}


SpaceSideParking::~SpaceSideParking(void)
{
	delete []m_pt3d;
	delete []m_pt;
	delete m_tips;
}
void SpaceSideParking:: setParams(double x,double y)
{
	this->m_dX = x;
	this->m_dY = y;
}
void SpaceSideParking:: setCar(const Car *car)
{
	double L = car->m_fLength * 1.5 + 1000;//侧方停车的车位长度是车辆长度的1.5倍加1米
	double W = car->m_fWidth + 800;//车宽+80cm
	double W2 =car->m_fWidth * 1.5 + 800; //1.5倍车宽+80cm
	double L2 = L;
	//左上角
	(m_pt3d+0)->x = m_dX - L / 2.0;
	(m_pt3d+0)->y = m_dY - W;

	//右上角
	(m_pt3d+1)->x = m_dX + L / 2.0;
	(m_pt3d+1)->y = (m_pt3d+0)->y;

	//右中拐角
	(m_pt3d+2)->x = (m_pt3d+1)->x;
	(m_pt3d+2)->y = (m_pt3d+1)->y + W;

	//右外拐角
	(m_pt3d+3)->x = (m_pt3d+2)->x + L2;
	(m_pt3d+3)->y = (m_pt3d+2)->y;

	//右下拐角
	(m_pt3d+4)->x = (m_pt3d+3)->x;
	(m_pt3d+4)->y = (m_pt3d+3)->y+W2;

	//左下拐角
	(m_pt3d+5)->x = (m_pt3d+0)->x-L2;
	(m_pt3d+5)->y = (m_pt3d+4)->y;

	//左外拐角
	(m_pt3d+6)->x = (m_pt3d+5)->x;
	(m_pt3d+6)->y = (m_pt3d+5)->y-W2;

	//左中拐角
	(m_pt3d+7)->x = (m_pt3d+6)->x+L2;
	(m_pt3d+7)->y = (m_pt3d+6)->y;

	//中心点
	(m_pt3d+8)->x = this->m_dX;
	(m_pt3d+8)->y = this->m_dY;

	double offset = abs((m_pt3d+2)->y - (m_pt3d+4)->y);
	m_tips->setParams(this->m_dX,this->m_dY + offset + offset/2);
}
 void SpaceSideParking:: Translate(double x,double y,double z)
 {
	 MathUtil::Translate(m_pt3d,SIZE_OF_VERTEX,x,y,z);
	 this->m_dX = (m_pt3d+8)->x;
	 this->m_dY = (m_pt3d+8)->y;

	 double offset = abs((m_pt3d+2)->y - (m_pt3d+4)->y);
	m_tips->setParams(this->m_dX,this->m_dY + offset + offset/2);
	 Util::LOG(L"SpaceSideParking:: Translate(%lf,%lf)",
		 this->m_dX,this->m_dY);
 }
 void SpaceSideParking:: Scale(double ratio)
 {
	 Scale(ratio,this->m_dX,this->m_dY,0);
 }
 void SpaceSideParking:: Scale(double ratio,double x,double y,double z)
 {
	 MathUtil::Translate(m_pt3d,SIZE_OF_VERTEX,-x,-y,-z);
	 MathUtil::Scale(m_pt3d,SIZE_OF_VERTEX,ratio);
	 MathUtil::Translate(m_pt3d,SIZE_OF_VERTEX,x,y,z);
	 this->m_dX = (m_pt3d+8)->x;
	 this->m_dY = (m_pt3d+8)->y;

	 double offset = abs((m_pt3d+2)->y - (m_pt3d+4)->y);
	m_tips->setParams(this->m_dX,this->m_dY + offset + offset/2);
 }
 void SpaceSideParking:: Rotate(double degree)
 {
	Rotate(degree,this->m_dX,this->m_dY,0);
 }
 void SpaceSideParking:: Rotate(double degree,double x,double y,double z)
 {
	 MathUtil::Translate(m_pt3d,SIZE_OF_VERTEX,-x,-y,-z);
	 MathUtil::RotateZ(m_pt3d,SIZE_OF_VERTEX,degree);
	 MathUtil::Translate(m_pt3d,SIZE_OF_VERTEX,x,y,z);
	 this->m_dX = (m_pt3d+8)->x;
	 this->m_dY = (m_pt3d+8)->y;

	 double offset = abs((m_pt3d+2)->y - (m_pt3d+4)->y);
	m_tips->setParams(this->m_dX,this->m_dY + offset + offset/2);
 }
 void SpaceSideParking:: draw(CDC &dc)
 {
	for(int i=0;i<SIZE_OF_VERTEX-1;++i)
	{
		(m_pt + i)->x = (m_pt3d + i)->x;
		(m_pt + i)->y = (m_pt3d + i)->y;
	}
	CPen pen,*poldpen;
	pen.CreatePen(PS_SOLID,1,RGB(255,128,0));
	poldpen = dc.SelectObject(&pen);

	dc.Polygon(m_pt,SIZE_OF_VERTEX - 1);

	dc.SelectObject(poldpen);
	pen.DeleteObject();

	pen.CreatePen(PS_DASH,1,RGB(255,128,0));
	poldpen = dc.SelectObject(&pen);
	dc.MoveTo(*(m_pt+2));
	dc.LineTo(*(m_pt+7));
	dc.SelectObject(poldpen);
	pen.DeleteObject();

	m_tips->draw(dc);
 }