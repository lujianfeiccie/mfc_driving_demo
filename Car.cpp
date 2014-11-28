#include "StdAfx.h"
#include "Car.h"
#include "MathUtil.h"
#include "Util.h"
Car::Car()
{
	m_degree = 0;
	m_wheel_front_left = new Wheel();
	m_wheel_front_right = new Wheel();
	m_wheel_rear_left = new Wheel();
	m_wheel_rear_right = new Wheel();

	pt3d_front = new ThreeDPoint[4]; //前车盖
	pt_front = new CPoint[4];

	pt3d_front_wheel = new ThreeDPoint[2]; //前轴
	pt_front_wheel = new CPoint[2];

	pt3d_mid = new ThreeDPoint[6]; //车身+中轴
	pt_mid = new CPoint[6];

	pt3d_rear_wheel = new ThreeDPoint[2]; //后轴
	pt_rear_wheel = new CPoint[2];

	pt3d_rear = new ThreeDPoint[4]; //后车盖
	pt_rear = new CPoint[4];

	
}

void Car::setParams(
	double x,

	double y,

	double ratio,

	double m_fLength, //长度(mm) 4415  

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


	m_dRatio = ratio;

	m_dX = x;
	m_dY = y;

	//前车盖
	for(int i=0;i<4;i++) (pt3d_front+i)->z = 0;
	
	(pt3d_front+0)->x = m_dX - m_fWidth / 2.0;(pt3d_front+0)->y =m_dY - m_fWheelbase / 2.0 - m_fWheel_diameter / 2.0 - m_fWheel_diameter / 5.0;

	(pt3d_front+1)->x = m_dX - m_fWidth / 2.0;(pt3d_front+1)->y =m_dY - m_fLength / 2.0;
	
	(pt3d_front+2)->x = m_dX + m_fWidth / 2.0;(pt3d_front+2)->y =m_dY - m_fLength / 2.0;

	(pt3d_front+3)->x = m_dX + m_fWidth / 2.0;(pt3d_front+3)->y =m_dY - m_fWheelbase / 2.0 - m_fWheel_diameter / 2.0 - m_fWheel_diameter / 5.0;
	
	//前车轴
	for(int i=0;i<2;i++) (pt3d_front_wheel+i)->z = 0;
	(pt3d_front_wheel+0)->x = m_dX - m_fWidth / 2.0;(pt3d_front_wheel+0)->y = m_dY - m_fWheelbase / 2.0;
	(pt3d_front_wheel+1)->x = m_dX + m_fWidth / 2.0;(pt3d_front_wheel+1)->y = m_dY - m_fWheelbase / 2.0;

	//车身
	for(int i=0;i<6;i++) (pt3d_mid + i)->z = 0;
	(pt3d_mid+0)->x = m_dX -  m_fWidth / 2.0;(pt3d_mid+0)->y = m_dY - m_fWheelbase / 2.0 + m_fWheel_diameter / 2.0 + m_fWheel_diameter / 5.0;
	(pt3d_mid+1)->x = m_dX -  m_fWidth / 2.0;(pt3d_mid+1)->y = m_dY + m_fWheelbase / 2.0 - m_fWheel_diameter / 2.0 - m_fWheel_diameter / 5.0;

	(pt3d_mid+2)->x = m_dX +  m_fWidth / 2.0;(pt3d_mid+2)->y = m_dY - m_fWheelbase / 2.0 + m_fWheel_diameter / 2.0 + m_fWheel_diameter / 5.0;
	(pt3d_mid+3)->x = m_dX +  m_fWidth / 2.0;(pt3d_mid+3)->y = m_dY + m_fWheelbase / 2.0 - m_fWheel_diameter / 2.0 - m_fWheel_diameter / 5.0;

	//中轴
	(pt3d_mid+4)->x = m_dX; (pt3d_mid+4)->y = m_dY - m_fWheelbase / 2.0;
	(pt3d_mid+5)->x = m_dX; (pt3d_mid+5)->y = m_dY + m_fWheelbase / 2.0;

	//前轮胎
	m_wheel_front_left->setParams( m_dX -m_fWidth / 2.0 ,m_dY - m_fWheelbase / 2.0, m_dX, m_dY,m_dRatio, m_fWheel_diameter);
	m_wheel_front_right->setParams( m_dX +m_fWidth / 2.0 ,m_dY - m_fWheelbase / 2.0, m_dX, m_dY,m_dRatio, m_fWheel_diameter);
	
	m_wheel_front_left->ScaleCar(m_dRatio);
	m_wheel_front_right->ScaleCar(m_dRatio);

	//后轮胎
	m_wheel_rear_left->setParams( m_dX -m_fWidth / 2.0 ,m_dY + m_fWheelbase / 2.0, m_dX, m_dY,m_dRatio, m_fWheel_diameter);
	m_wheel_rear_right->setParams( m_dX +m_fWidth / 2.0 ,m_dY + m_fWheelbase / 2.0, m_dX, m_dY,m_dRatio, m_fWheel_diameter);
	
	m_wheel_rear_left->ScaleCar(m_dRatio);
	m_wheel_rear_right->ScaleCar(m_dRatio);

	//后轴
	for(int i=0;i<2;i++) (pt3d_rear_wheel + i)->z = 0;
	(pt3d_rear_wheel+0)->x = m_dX - m_fWidth / 2.0;(pt3d_rear_wheel+0)->y = m_dY + m_fWheelbase / 2.0;
	(pt3d_rear_wheel+1)->x = m_dX + m_fWidth / 2.0;(pt3d_rear_wheel+1)->y = m_dY + m_fWheelbase / 2.0;

	//后车盖
	for(int i=0;i<4;i++) (pt3d_rear+i)->z = 0;
	
	(pt3d_rear+0)->x = m_dX - m_fWidth / 2.0;(pt3d_rear+0)->y =m_dY + m_fWheelbase / 2.0 + m_fWheel_diameter / 2.0 + m_fWheel_diameter / 5.0;

	(pt3d_rear+1)->x = m_dX - m_fWidth / 2.0;(pt3d_rear+1)->y =m_dY + m_fLength / 2.0 ;
	
	(pt3d_rear+2)->x = m_dX + m_fWidth / 2.0;(pt3d_rear+2)->y =m_dY + m_fLength / 2.0 ;

	(pt3d_rear+3)->x = m_dX + m_fWidth / 2.0;(pt3d_rear+3)->y =m_dY + m_fWheelbase / 2.0 + m_fWheel_diameter / 2.0 + m_fWheel_diameter / 5.0;


	Scale(m_dRatio);
}

void Car::Translate(double x,double y,double z)
{
	MathUtil::Translate(pt3d_front,4,x,y,z);

	MathUtil::Translate(pt3d_front_wheel,2,x,y,z);

	MathUtil::Translate(pt3d_mid,6,x,y,z);

	MathUtil::Translate(pt3d_rear_wheel,2,x,y,z);
	
	MathUtil::Translate(pt3d_rear,4,x,y,z);

	m_wheel_front_left->Translate(x,y,z);
	m_wheel_front_right->Translate(x,y,z);

	m_wheel_rear_left->Translate(x,y,z);
	m_wheel_rear_right->Translate(x,y,z);

	if(x<0) --m_dX; else if(x>0) ++m_dX;
	if(y<0) --m_dY; else if(y>0) ++m_dY;
	
	Util::LOG(L"(%lf , %lf)",m_dX,m_dY);
}
void Car::turn_left()
{
	m_wheel_front_left->turn_left();
	m_wheel_front_right->turn_left();
	double a = 90.0 - (double)m_wheel_front_right->m_degree - m_degree;
	m_radius = tan(a * PI / 180) * m_fWheelbase;
	m_radius*=m_dRatio;
	Util::LOG(L"turn left degree=%lf m_radius=%lf",m_wheel_front_right->m_degree,m_radius);
}
void Car::turn_right()
{
	m_wheel_front_left->turn_right();
	m_wheel_front_right->turn_right();

	double a = 90.0 - (double)m_wheel_front_right->m_degree - m_degree;
	m_radius = tan(a * PI / 180) * m_fWheelbase;
	
	m_radius*=m_dRatio;

	//计算旋转中心
	m_rotate_center.x = (pt3d_rear_wheel+1)->x + cos(m_degree * PI / 180) * m_radius;
	m_rotate_center.y = (pt3d_rear_wheel+1)->y + sin(m_degree * PI / 180) * m_radius;

	Util::LOG(L"wheel degree=%lf car degree=%lf m_radius=%lf center(%lf,%lf)",m_wheel_front_right->m_degree,m_degree,m_radius,m_rotate_center.x,m_rotate_center.y);
}
void Car::Scale(double ratio)
{
	Scale(ratio,m_dX,m_dY,0);
}
void Car::Scale(double ratio,double x,double y,double z)
{
	//前车盖
	MathUtil::Translate(pt3d_front,4,-x,-y,z);
	MathUtil::Scale(pt3d_front,4,ratio);
	MathUtil::Translate(pt3d_front,4,x,y,z);


	//前轮轴
	MathUtil::Translate(pt3d_front_wheel,2,-x,-y,z);
	MathUtil::Scale(pt3d_front_wheel,2,ratio);
	MathUtil::Translate(pt3d_front_wheel,2,x,y,z);


	//车身+中轴
	MathUtil::Translate(pt3d_mid,6,-x,-y,z);
	MathUtil::Scale(pt3d_mid,6,ratio);
	MathUtil::Translate(pt3d_mid,6,x,y,z);


	//后轮轴
	MathUtil::Translate(pt3d_rear_wheel,2,-x,-y,z);
	MathUtil::Scale(pt3d_rear_wheel,2,ratio);
	MathUtil::Translate(pt3d_rear_wheel,2,x,y,z);

	//后车盖
	MathUtil::Translate(pt3d_rear,4,-x,-y,z);
	MathUtil::Scale(pt3d_rear,4,ratio);
	MathUtil::Translate(pt3d_rear,4,x,y,z);

	m_dRatio *= ratio;
}

void Car::Rotate(double degree)
{
	Rotate(degree,m_dX,m_dY,0);
}
void Car::Rotate(double degree,double x,double y,double z)
{
	//前车盖
	MathUtil::Translate(pt3d_front,4,-x,-y,z);
	MathUtil::RotateZ(pt3d_front,4,degree);
	MathUtil::Translate(pt3d_front,4,x,y,z);


	//前轮轴
	MathUtil::Translate(pt3d_front_wheel,2,-x,-y,z);
	MathUtil::RotateZ(pt3d_front_wheel,2,degree);
	MathUtil::Translate(pt3d_front_wheel,2,x,y,z);


	//车身+中轴
	MathUtil::Translate(pt3d_mid,6,-x,-y,z);
	MathUtil::RotateZ(pt3d_mid,6,degree);
	MathUtil::Translate(pt3d_mid,6,x,y,z);


	//后轮轴
	MathUtil::Translate(pt3d_rear_wheel,2,-x,-y,z);
	MathUtil::RotateZ(pt3d_rear_wheel,2,degree);
	MathUtil::Translate(pt3d_rear_wheel,2,x,y,z);

	//后车盖
	MathUtil::Translate(pt3d_rear,4,-x,-y,z);
	MathUtil::RotateZ(pt3d_rear,4,degree);
	MathUtil::Translate(pt3d_rear,4,x,y,z);

	//轮胎
	m_wheel_front_left->Rotate(degree,x,y,z);
	m_wheel_front_right->Rotate(degree,x,y,z);
	m_wheel_rear_left->Rotate(degree,x,y,z);
	m_wheel_rear_right->Rotate(degree,x,y,z);

	m_degree +=degree;
}
void Car::go_forward()
{
	Util::LOG(L"front=%lf car=%lf",m_wheel_front_left->m_degree,m_degree);
	if(m_wheel_front_left->m_degree - m_degree ==0 )
	{
		Translate(sin(m_wheel_front_left->m_degree * PI / 180.0),
			      -cos(m_wheel_front_left->m_degree * PI / 180.0),
				  0);
	 
	}
	else
	{
		Rotate(1,m_rotate_center.x,m_rotate_center.y,0);

	}
}
void Car::go_backward()
{
	if(m_wheel_front_left->m_degree - m_degree ==0 )
	{
		Translate(sin(m_wheel_front_left->m_degree * PI / 180.0),
			      cos(m_wheel_front_left->m_degree * PI / 180.0),
				  0);
	 //Rotate(1,
	}
	else
	{
		Rotate(-1,m_rotate_center.x,m_rotate_center.y,0);

	}
}
void Car::draw(CPaintDC &dc)
{
	//绘制前车盖
	for(int i=0;i<4;i++)
	{
	   (pt_front + i)->x = (pt3d_front+i)->x;
	   (pt_front + i)->y = (pt3d_front+i)->y;
	}
	dc.MoveTo(*(pt_front+0));
	dc.LineTo(*(pt_front+1));
	dc.LineTo(*(pt_front+2));
	dc.LineTo(*(pt_front+3));

	//绘制前轮轴
	for(int i=0;i<2;i++)
	{
	   (pt_front_wheel + i)->x = (pt3d_front_wheel+i)->x;
	   (pt_front_wheel + i)->y = (pt3d_front_wheel+i)->y;
	}
	dc.MoveTo(*(pt_front_wheel+0));
	dc.LineTo(*(pt_front_wheel+1));

	//绘制车身+中轴
	for(int i=0;i<6;i++)
	{
	   (pt_mid + i)->x = (pt3d_mid+i)->x;
	   (pt_mid + i)->y = (pt3d_mid+i)->y;
	}
	dc.MoveTo(*(pt_mid+0));
	dc.LineTo(*(pt_mid+1));

	dc.MoveTo(*(pt_mid+2));
	dc.LineTo(*(pt_mid+3));

	dc.MoveTo(*(pt_mid+4));
	dc.LineTo(*(pt_mid+5));

	//绘制后轮轴
	for(int i=0;i<2;i++)
	{
	   (pt_rear_wheel + i)->x = (pt3d_rear_wheel+i)->x;
	   (pt_rear_wheel + i)->y = (pt3d_rear_wheel+i)->y;
	}
	dc.MoveTo(*(pt_rear_wheel+0));
	dc.LineTo(*(pt_rear_wheel+1));

	//绘制前车盖
	for(int i=0;i<4;i++)
	{
	   (pt_rear + i)->x = (pt3d_rear+i)->x;
	   (pt_rear + i)->y = (pt3d_rear+i)->y;
	}
	dc.MoveTo(*(pt_rear+0));
	dc.LineTo(*(pt_rear+1));
	dc.LineTo(*(pt_rear+2));
	dc.LineTo(*(pt_rear+3));

	m_wheel_front_left->draw(dc);
	m_wheel_front_right->draw(dc);
	m_wheel_rear_left->draw(dc);
	m_wheel_rear_right->draw(dc);
}



Car::~Car(void)
{
	delete m_wheel_front_left;//左前轮
	delete m_wheel_front_right;//右前轮

	delete m_wheel_rear_left;//左后轮
	delete m_wheel_rear_right; //右后轮

	delete []pt3d_front; //前车盖
	delete []pt_front;

	delete []pt3d_front_wheel; //前轴
	delete []pt_front_wheel;

	delete []pt3d_mid; //车身+中轴
	delete []pt_mid;

	delete []pt3d_rear_wheel; //前轴
	delete []pt_rear_wheel;

	delete []pt3d_rear; //后车盖
	delete []pt_rear;

}