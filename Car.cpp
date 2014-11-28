#include "StdAfx.h"
#include "Car.h"
#include "MathUtil.h"
#include "Util.h"
Car::Car(int x,int y,double ratio)
{

	m_wheel = new Wheel(x,y,0,0,ratio);

	m_dRatio = ratio;

	m_dX = x;
	m_dY = y;

	
	pt3d_front = new ThreeDPoint[4]; //前车盖
	pt_front = new CPoint[4];

	pt3d_front_wheel = new ThreeDPoint[2]; //前轴
	pt_front_wheel = new CPoint[2];

	pt3d_mid = new ThreeDPoint[6]; //车身+中轴
	pt_mid = new CPoint[6];

	pt3d_rear_wheel = new ThreeDPoint[2]; //前轴
	pt_rear_wheel = new CPoint[2];

	pt3d_rear = new ThreeDPoint[4]; //后车盖
	pt_rear = new CPoint[4];

	setParams(4415, //长度(mm) 4415  

			  1674,  //宽度(mm) 1674  

              1415, //高度(mm) 1415  

			   2471, //轴距(mm) 2471  

				1429, //前轮距(mm) 1429 

				1422,  //后轮距(mm) 1422  

				381 //轮胎直径(mm) 381  R15 inch 
				);
}

void Car::setParams(double m_fLength, //长度(mm) 4415  

    double m_fWidth,  //宽度(mm) 1674  

    double m_fHeight, //高度(mm) 1415  

    double m_fWheelbase, //轴距(mm) 2471  

    double m_fFront_tread, //前轮距(mm) 1429 

    double m_fRear_tread,  //后轮距(mm) 1422  

    double m_fWheel_diameter //轮胎直径 
	)
{
	this->m_fLength = m_fLength;
	this->m_fWidth = m_fWidth;
	this->m_fHeight = m_fHeight;
	this->m_fWheelbase = m_fWheelbase;
	this->m_fFront_tread = m_fFront_tread;
	this->m_fRear_tread = m_fRear_tread;
	this->m_fWheel_diameter = m_fWheel_diameter;




	for(int i=0;i<4;i++) (pt3d_front+i)->z = 0;
	
	(pt3d_front+0)->x = m_dX - m_fWidth / 2.0;(pt3d_front+0)->y =m_dY - m_fWheelbase / 2.0 - m_fWheel_diameter / 2.0 - m_fWheel_diameter / 5.0;

	(pt3d_front+1)->x = m_dX - m_fWidth / 2.0;(pt3d_front+1)->y =m_dY - m_fLength / 2.0;
	
	(pt3d_front+2)->x = m_dX + m_fWidth / 2.0;(pt3d_front+2)->y =m_dY - m_fLength / 2.0;

	(pt3d_front+3)->x = m_dX + m_fWidth / 2.0;(pt3d_front+3)->y =m_dY - m_fWheelbase / 2.0 - m_fWheel_diameter / 2.0 - m_fWheel_diameter / 5.0;
	

/*	m_wheel->Translate(-m_dX,-m_dY,0);
	m_wheel->Scale(m_dRatio);
	m_wheel->Translate(m_dX,m_dY,0);*/


/*	ThreeDPoint temp_pt[1];
	temp_pt[0].x = m_dX;temp_pt[0].y = m_dY;temp_pt[0].z = 0;
	MathUtil::Scale(temp_pt,1,m_dRatio);
	m_dX = temp_pt[0].x ; m_dY = temp_pt[0].y ;*/

	Scale(m_dRatio);

		//scale wheel
	m_wheel->setParams( m_dX - m_fWidth / 2.0 ,m_dY - m_fWheelbase / 2.0, m_dX, m_dY,m_dRatio, m_fWheel_diameter);

}


Car::~Car(void)
{
	delete m_wheel;

}
void Car::Translate(double x,double y,double z)
{
	MathUtil::Translate(pt3d_front,4,x,y,z);

	if(x<0) --m_dX; else if(x>0) ++m_dX;

	if(y<0) --m_dY; else if(y>0) ++m_dY;
	
	Util::LOG(L"(%lf , %lf)",m_dX,m_dY);
}
void Car::Scale(double ratio)
{
	//Scale car
	Util::LOG(L"before (%lf , %lf) ratio = %lf",pt3d_front->x,pt3d_front->y,m_dRatio);
	MathUtil::Translate(pt3d_front,4,-m_dX,-m_dY,0);
	MathUtil::Scale(pt3d_front,4,ratio);
	MathUtil::Translate(pt3d_front,4,m_dX,m_dY,0);

	m_dRatio *= ratio;
	Util::LOG(L"after (%lf , %lf) ratio = %lf",pt3d_front->x,pt3d_front->y,m_dRatio);
}

void Car::draw(CPaintDC &dc)
{
	for(int i=0;i<4;i++)
	{
	   (pt_front + i)->x = (pt3d_front+i)->x;
	   (pt_front + i)->y = (pt3d_front+i)->y;
	}
	dc.MoveTo(*(pt_front+0));
	dc.LineTo(*(pt_front+1));
	dc.LineTo(*(pt_front+2));
	dc.LineTo(*(pt_front+3));

	m_wheel->draw(dc);
}