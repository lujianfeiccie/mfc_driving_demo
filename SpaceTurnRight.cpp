#include "StdAfx.h"
#include "SpaceTurnRight.h"
#include "Util.h"
#define SIZE_OF_VERTEX 7

SpaceTurnRight::SpaceTurnRight(void)
{
	Util::LOG(L"SpaceTurnRight");
	m_bFirstDraw = TRUE;
	m_pt3d = new ThreeDPoint[SIZE_OF_VERTEX];
	m_pt = new CPoint[SIZE_OF_VERTEX];
	m_tips = new ControlTips;
	for(int i=0;i<SIZE_OF_VERTEX;i++) (m_pt3d+i)->z = 0;
}
void SpaceTurnRight::setParams(double x,double y)
{
	this->m_dX = x;
	this->m_dY = y;

	(m_pt3d+SIZE_OF_VERTEX-1)->x = this->m_dX;
	(m_pt3d+SIZE_OF_VERTEX-1)->y = this->m_dX;
}
void SpaceTurnRight::setCar(const Car *car)
{
	
	double width = car->m_fLength * 3;
	(m_pt3d+0)->x = this->m_dX - width / 2;//���Ͻ�
	(m_pt3d+0)->y = this->m_dY - width / 2;

	(m_pt3d+1)->x = this->m_dX + width / 2;//���Ͻ�
	(m_pt3d+1)->y = (m_pt3d+0)->y;

	(m_pt3d+2)->x = (m_pt3d+1)->x;//���½�
	(m_pt3d+2)->y = (m_pt3d+1)->y + car->m_fWheelbase + 1000;//·�������+1��

	(m_pt3d+3)->x = (m_pt3d+0)->x + car->m_fWheelbase + 1000;//�ڹս�
	(m_pt3d+3)->y = (m_pt3d+0)->y + car->m_fWheelbase + 1000;

	(m_pt3d+4)->x = (m_pt3d+3)->x;//���ҽ�
	(m_pt3d+4)->y = this->m_dY + width / 2;

	(m_pt3d+5)->x = (m_pt3d+0)->x;//�����
	(m_pt3d+5)->y = this->m_dY + width / 2;

	m_tips->setParams((m_pt3d+3)->x+width/3, //�ڹս�x
					  (m_pt3d+2)->y-width/3  //���½�y
					  );
}

 void SpaceTurnRight::Translate(double x,double y,double z)
 {
	 MathUtil::Translate(m_pt3d,SIZE_OF_VERTEX,x,y,z);
	 this->m_dX = (m_pt3d + SIZE_OF_VERTEX - 1)->x;
	 this->m_dY = (m_pt3d + SIZE_OF_VERTEX - 1)->y;

	 //������ʾλ��
	double width = abs((m_pt3d+0)->x -(m_pt3d+3)->x)/2;
	m_tips->setParams((m_pt3d+3)->x+width, //�ڹս�x
					  (m_pt3d+2)->y-width  //���½�y
					  );
	 Util::LOG(L"SpaceTurnRight translate(%lf,%lf)",this->m_dX,this->m_dY);
 }
 void SpaceTurnRight::Scale(double ratio)
 {
	 Scale(ratio,m_dX,m_dY,0);
 }
 void SpaceTurnRight::Scale(double ratio,double x,double y,double z)
 {
	MathUtil::Translate(m_pt3d,SIZE_OF_VERTEX,-x,-y,-z);
	MathUtil::Scale(m_pt3d,SIZE_OF_VERTEX,ratio);
	MathUtil::Translate(m_pt3d,SIZE_OF_VERTEX,x,y,z);

	//������ʾλ��
	double width = abs((m_pt3d+0)->x -(m_pt3d+3)->x)/2;
	m_tips->setParams((m_pt3d+3)->x+width, //�ڹս�x
					  (m_pt3d+2)->y+width / 7  //���½�y
					  );
	
 }
 void SpaceTurnRight::Rotate(double degree)
 {
	 Rotate(degree,m_dX,m_dY,0);
 }
 void SpaceTurnRight::Rotate(double degree,double x,double y,double z)
 {
    MathUtil::Translate(m_pt3d,SIZE_OF_VERTEX,-x,-y,-z);
	MathUtil::RotateZ(m_pt3d,SIZE_OF_VERTEX,degree);
	MathUtil::Translate(m_pt3d,SIZE_OF_VERTEX,x,y,z);
	 this->m_dX = (m_pt3d + SIZE_OF_VERTEX - 1)->x;
	 this->m_dY = (m_pt3d + SIZE_OF_VERTEX - 1)->y;

	//������ʾλ��
	double width = abs((m_pt3d+0)->x -(m_pt3d+3)->x)/2;
	m_tips->setParams((m_pt3d+3)->x+width, //�ڹս�x
					  (m_pt3d+2)->y-width  //���½�y
					  );
 }
 void SpaceTurnRight::draw(CDC &dc)
{
    if(m_bFirstDraw){
	for(int i=0;i<SIZE_OF_VERTEX-1;++i)
	{
		(m_pt+i)->x = (m_pt3d+i)->x;
		(m_pt+i)->y = (m_pt3d+i)->y;
	}
	}
	CPen pen;   //���ƻ���
	pen.CreatePen(PS_SOLID,2,RGB(255,128,0));
	CPen* poldpen = dc.SelectObject(&pen);

	dc.Polygon(m_pt,SIZE_OF_VERTEX-1);


	m_bFirstDraw = FALSE;
	dc.SelectObject(poldpen);
	pen.DeleteObject();

	m_tips->draw(dc);
	//pen.DeleteObject();
}
SpaceTurnRight::~SpaceTurnRight(void)
{
	Util::LOG(L"~SpaceTurnRight");
	delete []m_pt3d;
	delete []m_pt;
}
 
