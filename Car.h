#pragma once
#include "IControl.h"
#include "MathUtil.h"
#include "Wheel.h"
class Car : public IControl
{
public:
	Car(int x,int y,double ratio);
	~Car(void);

	void setParams(double m_fLength, //长度(mm) 4415  

    double m_fWidth,  //宽度(mm) 1674  

    double m_fHeight, //高度(mm) 1415  

    double m_fWheelbase, //轴距(mm) 2471  

    double m_fFront_tread, //前轮距(mm) 1429 

    double m_fRear_tread,  //后轮距(mm) 1422  

    double m_fWheel_diameter //轮胎直径 
	);
	double m_fLength; //长度(mm) 4415  

    double m_fWidth;  //宽度(mm) 1674  

    double m_fHeight; //高度(mm) 1415  

    double m_fWheelbase; //轴距(mm) 2471  

    double m_fFront_tread; //前轮距(mm) 1429 

    double m_fRear_tread;  //后轮距(mm) 1422  

    double m_fWheel_diameter; //轮胎直径 

    double m_fWheel_width; //轮胎厚度 

	ThreeDPoint* pt3d_front; //前车盖
	CPoint* pt_front;

	ThreeDPoint* pt3d_front_wheel; //前轴
	CPoint* pt_front_wheel;

	ThreeDPoint* pt3d_mid; //车身
	CPoint* pt_mid;

	ThreeDPoint* pt3d_rear_wheel; //后轴
	CPoint* pt_rear_wheel;

	ThreeDPoint* pt3d_rear; //后车盖
	CPoint* pt_rear;

	Wheel* m_wheel;

	void Translate(double x,double y,double z);
	void Scale(double ratio);	
	void draw(CPaintDC &dc);
};

