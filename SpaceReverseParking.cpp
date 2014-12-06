#include "StdAfx.h"
#include "SpaceReverseParking.h"
#define SIZE_OF_VERTEX 9

SpaceReverseParking::SpaceReverseParking(void)
{
	 m_pt3d = new ThreeDPoint[SIZE_OF_VERTEX];
	 m_pt = new CPoint[SIZE_OF_VERTEX];
	 m_tips = new ControlTips;
	 for(int i=0;i<SIZE_OF_VERTEX;++i) (m_pt3d + i)->z = 0;
}
 void SpaceReverseParking::setParams(double x,double y)
 {
	this->m_dX = x;
	this->m_dY = y;
 }
 void SpaceReverseParking::setCar(const Car *car)
 {
	 double W = car->m_fWidth + 600;//W（库宽）：车身宽（不含倒车镜）加60cm
	 double L = car->m_fLength + 700; //L（库位长）：车身长加70cm
	 double S = car->m_fLength * 1.5; //S（车道宽）：车身长的1.5倍
	 double H = car->m_fLength * 1.5;//H（车库距控制线）：车身长的1.5倍

	 double length = H * 2 + W; //场地长
	 double width = S + L ; //场地宽
	  //左上角
	 (m_pt3d + 0)->x = this->m_dX - length / 2;
	 (m_pt3d + 0)->y = this->m_dY - width / 2;

	 //右上角
	 (m_pt3d + 1)->x = this->m_dX + length / 2;
	 (m_pt3d + 1)->y = (m_pt3d + 0)->y;

	 //右下外拐角
	 (m_pt3d + 2)->x = (m_pt3d + 1)->x;
	 (m_pt3d + 2)->y = (m_pt3d + 1)->y + S;

	 //右下中内拐角
	 (m_pt3d + 3)->x = (m_pt3d + 2)->x - H;
	 (m_pt3d + 3)->y = (m_pt3d + 2)->y;

	 //右下底拐角
	 (m_pt3d + 4)->x = (m_pt3d + 3)->x;
	 (m_pt3d + 4)->y = (m_pt3d + 3)->y + L;

	 //左下底拐角
	 (m_pt3d + 5)->x = (m_pt3d + 4)->x - W;
	 (m_pt3d + 5)->y = (m_pt3d + 4)->y;

	 //左下中内拐角
	 (m_pt3d + 6)->x = (m_pt3d + 5)->x;
	 (m_pt3d + 6)->y = (m_pt3d + 3)->y;


	  //左下外拐角
	 (m_pt3d + 7)->x = (m_pt3d + 0)->x;
	 (m_pt3d + 7)->y = (m_pt3d + 2)->y;

	 //文字提示
	 m_tips->setParams((m_pt3d + 7)->x+W/2,(m_pt3d + 3)->y+W/2);

	 //中心点
	 (m_pt3d + 8)->x = this->m_dX; 
     (m_pt3d + 8)->y = this->m_dY;
 }



void SpaceReverseParking:: Translate(double x,double y,double z)
{
	MathUtil::Translate(m_pt3d,SIZE_OF_VERTEX,x,y,z);
	this->m_dX = (m_pt3d + 8)->x; 
    this->m_dY = (m_pt3d + 8)->y;

	 double width = abs((m_pt3d + 4)->x -  (m_pt3d + 5)->x)/2;
	 //文字提示
	m_tips->setParams((m_pt3d + 7)->x - width,(m_pt3d + 3)->y + width);

	Util::LOG(L" SpaceReverseParking:: Translate (%lf,%lf)",this->m_dX,this->m_dY);
}
void SpaceReverseParking:: Scale(double ratio)
{
	Scale(ratio,this->m_dX,this->m_dY,0);
}
void SpaceReverseParking:: Scale(double ratio,double x,double y,double z)
{
	MathUtil::Translate(m_pt3d,SIZE_OF_VERTEX,-x,-y,-z);
	MathUtil::Scale(m_pt3d,SIZE_OF_VERTEX,ratio);
	MathUtil::Translate(m_pt3d,SIZE_OF_VERTEX,x,y,z);

	this->m_dX = (m_pt3d + 8)->x; 
    this->m_dY = (m_pt3d + 8)->y;

	 double width = abs((m_pt3d + 4)->x -  (m_pt3d + 5)->x)/2;
	 //文字提示
	m_tips->setParams((m_pt3d + 7)->x - width,(m_pt3d + 3)->y + width);

}
void SpaceReverseParking::Rotate(double degree)
{
	Rotate(degree,this->m_dX,this->m_dY,0);
}
void SpaceReverseParking::Rotate(double degree,double x,double y,double z)
{
	MathUtil::Translate(m_pt3d,SIZE_OF_VERTEX,-x,-y,-z);
	MathUtil::RotateZ(m_pt3d,SIZE_OF_VERTEX,degree);
	MathUtil::Translate(m_pt3d,SIZE_OF_VERTEX,x,y,z);

	this->m_dX = (m_pt3d + 8)->x; 
    this->m_dY = (m_pt3d + 8)->y;

	 double width = abs((m_pt3d + 4)->x -  (m_pt3d + 5)->x)/2;
	 //文字提示
	m_tips->setParams((m_pt3d + 7)->x -width,(m_pt3d + 3)->y+width);

}
void SpaceReverseParking:: draw(CDC &dc)
{
	for(int i = 0; i<SIZE_OF_VERTEX;++i)
	{
		(m_pt+i)->x = (m_pt3d+i)->x ; 
		(m_pt+i)->y = (m_pt3d+i)->y ; 
	}
	CPen pen;   //绘制画笔
	pen.CreatePen(PS_SOLID,2,RGB(255,128,0));
	CPen* poldpen = dc.SelectObject(&pen);

	dc.MoveTo(*(m_pt+0));
	dc.LineTo(*(m_pt+1));

	dc.MoveTo(*(m_pt+2));
	dc.LineTo(*(m_pt+3));
	dc.LineTo(*(m_pt+4));
	dc.LineTo(*(m_pt+5));
	dc.LineTo(*(m_pt+6));
	dc.LineTo(*(m_pt+7));

	dc.SelectObject(poldpen);
	pen.DeleteObject();

	pen.CreatePen(PS_DASH,1,RGB(255,128,0));
	poldpen = dc.SelectObject(&pen);

	dc.MoveTo(*(m_pt+1));
	dc.LineTo(*(m_pt+2));

	dc.MoveTo(*(m_pt+7));
	dc.LineTo(*(m_pt+0));

	dc.SelectObject(poldpen);
	pen.DeleteObject();

	m_tips->draw(dc);
}

SpaceReverseParking::~SpaceReverseParking(void)
{
	delete []m_pt3d;
	delete []m_pt;
}