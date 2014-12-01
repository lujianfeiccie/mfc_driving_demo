#pragma once
#include "IControl.h"
#include "MathUtil.h"
#include "Wheel.h"
class Car : public IControl
{
public:
	Car();
	~Car(void);

	void setParams(
	double x,

	double y,

	double m_fLength, //����(mm) 4415  

    double m_fWidth,  //���(mm) 1674  

    double m_fHeight, //�߶�(mm) 1415  

    double m_fWheelbase, //���(mm) 2471  

    double m_fFront_tread, //ǰ�־�(mm) 1429 

    double m_fRear_tread,  //���־�(mm) 1422  

    double m_fWheel_diameter, //��ֱ̥�� 

	double m_fWheel_width //��̥���
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

	Wheel* m_wheel_front_left; //ǰ��
	Wheel* m_wheel_front_right;

	Wheel* m_wheel_rear_left;//����
	Wheel* m_wheel_rear_right;

	double m_radius; //ת��뾶
	ThreeDPoint m_rotate_center; //ת�����Բ��
	void Translate(double x,double y,double z);
	void turn_left();
	void turn_right();	
	void Scale(double ratio);
	void Scale(double ratio,double x,double y,double z);
	void Rotate(double degree);
	void Rotate(double degree,double x,double y,double z);
	void go_forward();
	void go_backward();
	void draw(CDC &dc);
	BOOL m_show_guide_line[4];
};

