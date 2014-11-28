#pragma once
#include "IControl.h"
#include "MathUtil.h"
#include "Wheel.h"
class Car : public IControl
{
public:
	Car(int x,int y,double ratio);
	~Car(void);

	void setParams(double m_fLength, //����(mm) 4415  

    double m_fWidth,  //���(mm) 1674  

    double m_fHeight, //�߶�(mm) 1415  

    double m_fWheelbase, //���(mm) 2471  

    double m_fFront_tread, //ǰ�־�(mm) 1429 

    double m_fRear_tread,  //���־�(mm) 1422  

    double m_fWheel_diameter //��ֱ̥�� 
	);
	double m_fLength; //����(mm) 4415  

    double m_fWidth;  //���(mm) 1674  

    double m_fHeight; //�߶�(mm) 1415  

    double m_fWheelbase; //���(mm) 2471  

    double m_fFront_tread; //ǰ�־�(mm) 1429 

    double m_fRear_tread;  //���־�(mm) 1422  

    double m_fWheel_diameter; //��ֱ̥�� 

    double m_fWheel_width; //��̥��� 

	ThreeDPoint* pt3d_front; //ǰ����
	CPoint* pt_front;

	ThreeDPoint* pt3d_front_wheel; //ǰ��
	CPoint* pt_front_wheel;

	ThreeDPoint* pt3d_mid; //����
	CPoint* pt_mid;

	ThreeDPoint* pt3d_rear_wheel; //����
	CPoint* pt_rear_wheel;

	ThreeDPoint* pt3d_rear; //�󳵸�
	CPoint* pt_rear;

	Wheel* m_wheel;

	void Translate(double x,double y,double z);
	void Scale(double ratio);	
	void draw(CPaintDC &dc);
};

