#include "StdAfx.h"
#include "Car.h"
#include "MathUtil.h"
#include "Util.h"
#define MAX_ANGLE_WHEEL 35
#define ERROR 0.0000001
Car::Car()
{
	for(int i=0;i<5;++i) m_show_guide_line[i] = FALSE;
	m_degree = 0;
	m_dRatio = 1;
	m_speed = 1;
	m_wheel_front_left = new Wheel();
	m_wheel_front_right = new Wheel();
	m_wheel_rear_left = new Wheel();
	m_wheel_rear_right = new Wheel();

	m_wheel_front_mid = new Wheel();


	pt3d_front = new ThreeDPoint[4]; //ǰ����
	pt_front = new CPoint[4];

	pt3d_front_wheel = new ThreeDPoint[2]; //ǰ��
	pt_front_wheel = new CPoint[2];

	pt3d_mid = new ThreeDPoint[6]; //����+����
	pt_mid = new CPoint[6];

	pt3d_rear_wheel = new ThreeDPoint[2]; //����
	pt_rear_wheel = new CPoint[2];

	pt3d_rear = new ThreeDPoint[4]; //�󳵸�
	pt_rear = new CPoint[4];

	
}

void Car::setParams(
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
	)
{
	this->m_fLength = m_fLength;
	this->m_fWidth = m_fWidth;
	this->m_fHeight = m_fHeight;
	this->m_fWheelbase = m_fWheelbase;
	this->m_fFront_tread = m_fFront_tread;
	this->m_fRear_tread = m_fRear_tread;
	this->m_fWheel_diameter = m_fWheel_diameter;



	m_dX = x;
	m_dY = y;

	//ǰ����
	for(int i=0;i<4;i++) (pt3d_front+i)->z = 0;
	
	(pt3d_front+0)->x = m_dX - m_fWidth / 2.0;(pt3d_front+0)->y =m_dY - m_fWheelbase / 2.0 - m_fWheel_diameter / 2.0 - m_fWheel_diameter / 5.0;

	(pt3d_front+1)->x = (pt3d_front+0)->x + m_fWidth/50; (pt3d_front+1)->y =m_dY - m_fLength / 2.0;
	
	(pt3d_front+2)->x = m_dX + m_fWidth / 2.0 - m_fWidth/50 ;(pt3d_front+2)->y =(pt3d_front+1)->y;

	(pt3d_front+3)->x = m_dX + m_fWidth / 2.0;(pt3d_front+3)->y =m_dY - m_fWheelbase / 2.0 - m_fWheel_diameter / 2.0 - m_fWheel_diameter / 5.0;
	
	//ǰ����
	for(int i=0;i<2;i++) (pt3d_front_wheel+i)->z = 0;
	(pt3d_front_wheel+0)->x = m_dX - m_fWidth / 2.0;(pt3d_front_wheel+0)->y = m_dY - m_fWheelbase / 2.0;
	(pt3d_front_wheel+1)->x = m_dX + m_fWidth / 2.0;(pt3d_front_wheel+1)->y = m_dY - m_fWheelbase / 2.0;

	//����
	for(int i=0;i<6;i++) (pt3d_mid + i)->z = 0;
	(pt3d_mid+0)->x = m_dX -  m_fWidth / 2.0;(pt3d_mid+0)->y = m_dY - m_fWheelbase / 2.0 + m_fWheel_diameter / 2.0 + m_fWheel_diameter / 5.0;
	(pt3d_mid+1)->x = m_dX -  m_fWidth / 2.0;(pt3d_mid+1)->y = m_dY + m_fWheelbase / 2.0 - m_fWheel_diameter / 2.0 - m_fWheel_diameter / 5.0;

	(pt3d_mid+2)->x = m_dX +  m_fWidth / 2.0;(pt3d_mid+2)->y = m_dY - m_fWheelbase / 2.0 + m_fWheel_diameter / 2.0 + m_fWheel_diameter / 5.0;
	(pt3d_mid+3)->x = m_dX +  m_fWidth / 2.0;(pt3d_mid+3)->y = m_dY + m_fWheelbase / 2.0 - m_fWheel_diameter / 2.0 - m_fWheel_diameter / 5.0;

	//����
	(pt3d_mid+4)->x = m_dX; (pt3d_mid+4)->y = m_dY - m_fWheelbase / 2.0;
	(pt3d_mid+5)->x = m_dX; (pt3d_mid+5)->y = m_dY + m_fWheelbase / 2.0;

	//ǰ��̥
	m_wheel_front_left->setParams( m_dX -m_fFront_tread / 2.0 ,
								  m_dY - m_fWheelbase / 2.0, 
								  m_dX, m_dY, m_fWheel_diameter,m_fWheel_width);

	m_wheel_front_mid->setParams( m_dX, 
		                           m_dY - m_fWheelbase / 2.0, 
		                            m_dX, m_dY, m_fWheel_diameter,m_fWheel_width);

	m_wheel_front_right->setParams( m_dX +m_fFront_tread / 2.0 ,m_dY - m_fWheelbase / 2.0, m_dX, m_dY, m_fWheel_diameter,m_fWheel_width);
	
	

	//����̥
	m_wheel_rear_left->setParams( m_dX -m_fRear_tread / 2.0 ,m_dY + m_fWheelbase / 2.0, m_dX, m_dY,m_fWheel_diameter,m_fWheel_width);
	m_wheel_rear_right->setParams( m_dX +m_fRear_tread / 2.0 ,m_dY + m_fWheelbase / 2.0, m_dX, m_dY,m_fWheel_diameter,m_fWheel_width);
	
	
	//����
	for(int i=0;i<2;i++) (pt3d_rear_wheel + i)->z = 0;
	(pt3d_rear_wheel+0)->x = m_dX - m_fWidth / 2.0;(pt3d_rear_wheel+0)->y = m_dY + m_fWheelbase / 2.0;
	(pt3d_rear_wheel+1)->x = m_dX + m_fWidth / 2.0;(pt3d_rear_wheel+1)->y = m_dY + m_fWheelbase / 2.0;


	//����Ackermannת�򼸺�ָʾ
	double degree_ackerman = 65;
	m_wheel_front_left->setRotationStick(degree_ackerman);
	m_wheel_front_right->setRotationStick(-degree_ackerman);

	//�󳵸�
	for(int i=0;i<4;i++) (pt3d_rear+i)->z = 0;
	
	(pt3d_rear+0)->x = m_dX - m_fWidth / 2.0;(pt3d_rear+0)->y =m_dY + m_fWheelbase / 2.0 + m_fWheel_diameter / 2.0 + m_fWheel_diameter / 5.0;

	(pt3d_rear+1)->x = m_dX - m_fWidth / 2.0+m_fWidth/50;(pt3d_rear+1)->y =m_dY + m_fLength / 2.0 ;
	
	(pt3d_rear+2)->x = m_dX + m_fWidth / 2.0-m_fWidth/50;(pt3d_rear+2)->y =m_dY + m_fLength / 2.0 ;

	(pt3d_rear+3)->x = m_dX + m_fWidth / 2.0;(pt3d_rear+3)->y =m_dY + m_fWheelbase / 2.0 + m_fWheel_diameter / 2.0 + m_fWheel_diameter / 5.0;

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
	m_wheel_front_mid->Translate(x,y,z);

	m_wheel_rear_left->Translate(x,y,z);
	m_wheel_rear_right->Translate(x,y,z);

	this->m_dX += x;
	this->m_dY += y;
	
	Util::LOG(L"Car::Translate(%lf,%lf)",m_dX,m_dY);
}
void calc_radius(double a,//�����복�ּн�
			     double wheelbase,//���
				 double *radius
			     )//������ת�뾶
{
	
	//������ת�뾶
	*radius = tan(a * PI / 180) * wheelbase;

}
void Car::calc_mid_front_wheel_position(double *x,double *y)
{
	//������ǰ��λ��
	double x_offset;
	double y_offset;
	if(m_degree >= 0 && m_degree <= 90) //1 quadrant
	{
		x_offset = (pt3d_rear_wheel+0)->x + abs((pt3d_rear_wheel+1)->x - (pt3d_rear_wheel+0)->x)/2;
		y_offset = (pt3d_rear_wheel+0)->y + abs((pt3d_rear_wheel+1)->y - (pt3d_rear_wheel+0)->y)/2;
	}
	else if(m_degree > -90 && m_degree < 0) //2 quadrant
	{
		x_offset = (pt3d_rear_wheel+0)->x + abs((pt3d_rear_wheel+1)->x - (pt3d_rear_wheel+0)->x)/2;
		y_offset = (pt3d_rear_wheel+0)->y - abs((pt3d_rear_wheel+1)->y - (pt3d_rear_wheel+0)->y)/2;
	}
	else if(m_degree > -180 && m_degree <= -90) //3 quadrant
	{
		x_offset = (pt3d_rear_wheel+0)->x - abs((pt3d_rear_wheel+1)->x - (pt3d_rear_wheel+0)->x)/2;
		y_offset = (pt3d_rear_wheel+0)->y - abs((pt3d_rear_wheel+1)->y - (pt3d_rear_wheel+0)->y)/2;
	}
	else if(m_degree > 90 && m_degree <= 180) //4 quadrant
	{
		x_offset = (pt3d_rear_wheel+0)->x - abs((pt3d_rear_wheel+1)->x - (pt3d_rear_wheel+0)->x)/2;
		y_offset = (pt3d_rear_wheel+0)->y + abs((pt3d_rear_wheel+1)->y - (pt3d_rear_wheel+0)->y)/2;
	}
	*x = x_offset;
	*y = y_offset;
}
void Car::calc_center_position(double degree_of_mid_wheel_bettween_car,double degree_of_car,ThreeDPoint pt_mid_front_wheel,ThreeDPoint* rotate_center)
{
	//������ת����
	if(degree_of_mid_wheel_bettween_car>0)//��̥��Գ���ƫ��
	{
		if(degree_of_car >=0 && degree_of_car < 90) //1st Quadrant
		{
		rotate_center->x = pt_mid_front_wheel.x + cos(degree_of_car * PI / 180) * m_radius;
		rotate_center->y = pt_mid_front_wheel.y + sin(degree_of_car * PI / 180) * m_radius;
		}
		else if(degree_of_car >=90 && degree_of_car < 180) //4th Quadrant
		{
		rotate_center->x = pt_mid_front_wheel.x - abs(cos(degree_of_car * PI / 180)) * m_radius;
    	rotate_center->y = pt_mid_front_wheel.y + abs(sin(degree_of_car * PI / 180)) * m_radius;
		}
		else if(degree_of_car >=-90 && degree_of_car < 0) //2nd Quadrant
		{
		rotate_center->x = pt_mid_front_wheel.x + abs(cos(degree_of_car * PI / 180)) * m_radius;
    	rotate_center->y = pt_mid_front_wheel.y - abs(sin(degree_of_car * PI / 180)) * m_radius;
		}
		else if(degree_of_car >=-180 && degree_of_car < -90) //3rd Quadrant
		{
		rotate_center->x = pt_mid_front_wheel.x - abs(cos(degree_of_car * PI / 180)) * m_radius;
    	rotate_center->y = pt_mid_front_wheel.y - abs(sin(degree_of_car * PI / 180)) * m_radius;
		}
	}
	else if(degree_of_mid_wheel_bettween_car<0)//��̥��Գ���ƫ��
	{
		if(degree_of_car >=0 && degree_of_car < 90) //1st Quadrant
		{
	    rotate_center->x = pt_mid_front_wheel.x - abs(cos(degree_of_car * PI / 180)) * m_radius;
    	rotate_center->y = pt_mid_front_wheel.y - abs(sin(degree_of_car * PI / 180)) * m_radius;
		}
		else if(degree_of_car >=90 && degree_of_car < 180) //4th Quadrant
		{
		rotate_center->x = pt_mid_front_wheel.x + abs(cos(degree_of_car * PI / 180)) * m_radius;
    	rotate_center->y = pt_mid_front_wheel.y - abs(sin(degree_of_car * PI / 180)) * m_radius;
		}
		else if(degree_of_car >=-90 && degree_of_car < 0) //2nd Quadrant
		{
		rotate_center->x = pt_mid_front_wheel.x - abs(cos(degree_of_car * PI / 180)) * m_radius;
    	rotate_center->y = pt_mid_front_wheel.y + abs(sin(degree_of_car * PI / 180)) * m_radius;
		}
		else if(degree_of_car >=-180 && degree_of_car < -90) //3rd Quadrant
		{
		rotate_center->x = pt_mid_front_wheel.x + abs(cos(degree_of_car * PI / 180)) * m_radius;
    	rotate_center->y = pt_mid_front_wheel.y + abs(sin(degree_of_car * PI / 180)) * m_radius;
		}
	}
}

void Car::calc_left_right_wheel(double degree_of_mid_wheel_between_car)
{
//������ת����
	if(degree_of_mid_wheel_between_car>0)//��̥��Գ���ƫ��
	{
		//������ǰ��ת��
		double hypotenuse = MathUtil::GetDistance(*(pt3d_front_wheel+1),m_rotate_center);
		double adjacent = m_fWheelbase * m_dRatio;
		double degree = 90 - acos(adjacent / hypotenuse) * 180 / PI;
		m_wheel_front_right->Rotate(-m_wheel_front_right->m_degree);
		m_wheel_front_right->Rotate(degree+m_degree);

		//������ǰ��ת��
		 hypotenuse = MathUtil::GetDistance(*(pt3d_front_wheel+0),m_rotate_center);
		 degree = 90 - acos(adjacent / hypotenuse) * 180 / PI;
		m_wheel_front_left->Rotate(-m_wheel_front_left->m_degree);
		m_wheel_front_left->Rotate(degree+m_degree);
	}
	else if(degree_of_mid_wheel_between_car<0)//��̥��Գ���ƫ��
	{
	    //������ǰ��ת��
		double hypotenuse = MathUtil::GetDistance(*(pt3d_front_wheel+1),m_rotate_center);
		double adjacent = m_fWheelbase * m_dRatio;
		double degree = 90 - acos(adjacent / hypotenuse) * 180 / PI;
		m_wheel_front_right->Rotate(-m_wheel_front_right->m_degree);
		m_wheel_front_right->Rotate(m_degree-degree);

		//������ǰ��ת��
		 hypotenuse = MathUtil::GetDistance(*(pt3d_front_wheel+0),m_rotate_center);
		 degree = 90 - acos(adjacent / hypotenuse) * 180 / PI;
		m_wheel_front_left->Rotate(-m_wheel_front_left->m_degree);
		m_wheel_front_left->Rotate(m_degree-degree);
	}
}
void Car::turn_left()
{
	double degree_offset = m_wheel_front_mid ->m_degree - m_degree;//��������ǰ�ּн�
	if(degree_offset<=-MAX_ANGLE_WHEEL) return;

	m_wheel_front_mid->turn_left();

	degree_offset = m_wheel_front_mid ->m_degree - m_degree;//��ת���ٴ�������ǰ�ֺͳ���ļн�
	Util::LOG(L"m_wheel_front_mid ->m_degree=%lf m_degree=%lf",m_wheel_front_mid ->m_degree,m_degree);
	double  a = 90.0 - abs((double)m_wheel_front_mid->m_degree - m_degree);//��������ǰ�ִ��߼н�

	//����뾶
	calc_radius(a,  
				m_fWheelbase * m_dRatio, //���
				&m_radius //�ó��뾶����
				);

	//������ǰ��λ��
	double x_offset,y_offset;
	calc_mid_front_wheel_position(&x_offset,&y_offset);

	//����Բ��λ��
	ThreeDPoint front_mid;
	front_mid.x = x_offset;
	front_mid.y = y_offset;
	calc_center_position(degree_offset,m_degree,front_mid,&m_rotate_center);
	
	//����������ת��
	calc_left_right_wheel(degree_offset);
//	Util::LOG(L"left degree = %lf  right degree = %lf degree=%lf degree_offset=%lf",m_wheel_front_left->m_degree,m_wheel_front_right->m_degree,m_degree,degree_offset);
}
void Car::turn_right()
{
	double degree_offset = m_wheel_front_mid ->m_degree - m_degree;//��ǰ�ֺͳ���ļн�
	if(degree_offset>=MAX_ANGLE_WHEEL) return;

	m_wheel_front_mid->turn_right();

	degree_offset = m_wheel_front_mid ->m_degree - m_degree;//��ת���ٴ�������ǰ�ֺͳ���ļн�
	double a = 90.0 - abs(degree_offset);//������ǰ�ִ��߼н�

	//����뾶
	calc_radius(a,m_fWheelbase * m_dRatio, &m_radius);
	
	//������ǰ��λ��
	double x_offset,y_offset;
	calc_mid_front_wheel_position(&x_offset,&y_offset);

	//����Բ��λ��
	ThreeDPoint front_mid;
	front_mid.x = x_offset;
	front_mid.y = y_offset;
	calc_center_position(degree_offset,m_degree,front_mid,&m_rotate_center);

	//����������ת��
	calc_left_right_wheel(degree_offset);
//	Util::LOG(L"left degree = %lf  right degree = %lf degree=%lf degree_offset=%lf",m_wheel_front_left->m_degree,m_wheel_front_right->m_degree,m_degree,degree_offset);
}
void Car::Scale(double ratio)
{
	Scale(ratio,m_dX,m_dY,0);
}
void Car::Scale(double ratio,double x,double y,double z)
{
	//ǰ����
	MathUtil::Translate(pt3d_front,4,-x,-y,z);
	MathUtil::Scale(pt3d_front,4,ratio);
	MathUtil::Translate(pt3d_front,4,x,y,z);


	//ǰ����
	MathUtil::Translate(pt3d_front_wheel,2,-x,-y,z);
	MathUtil::Scale(pt3d_front_wheel,2,ratio);
	MathUtil::Translate(pt3d_front_wheel,2,x,y,z);


	//����+����
	MathUtil::Translate(pt3d_mid,6,-x,-y,z);
	MathUtil::Scale(pt3d_mid,6,ratio);
	MathUtil::Translate(pt3d_mid,6,x,y,z);


	//������
	MathUtil::Translate(pt3d_rear_wheel,2,-x,-y,z);
	MathUtil::Scale(pt3d_rear_wheel,2,ratio);
	MathUtil::Translate(pt3d_rear_wheel,2,x,y,z);

	//�󳵸�
	MathUtil::Translate(pt3d_rear,4,-x,-y,z);
	MathUtil::Scale(pt3d_rear,4,ratio);
	MathUtil::Translate(pt3d_rear,4,x,y,z);

	//�ĸ�����
	m_wheel_front_left->ScaleCar(ratio);
	m_wheel_front_right->ScaleCar(ratio);

	m_wheel_rear_left->ScaleCar(ratio);
	m_wheel_rear_right->ScaleCar(ratio);

	//�м���
	m_wheel_front_mid->ScaleCar(ratio);

	m_dRatio = ratio;
	Util::LOG(L"m_dRatio=%lf",m_dRatio);
}

void Car::Rotate(double degree)
{
	Rotate(degree,m_dX,m_dY,0);
}
void Car::Rotate(double degree,double x,double y,double z)
{
	//ǰ����
	MathUtil::Translate(pt3d_front,4,-x,-y,z);
	MathUtil::RotateZ(pt3d_front,4,degree);
	MathUtil::Translate(pt3d_front,4,x,y,z);


	//ǰ����
	MathUtil::Translate(pt3d_front_wheel,2,-x,-y,z);
	MathUtil::RotateZ(pt3d_front_wheel,2,degree);
	MathUtil::Translate(pt3d_front_wheel,2,x,y,z);


	//����+����
	MathUtil::Translate(pt3d_mid,6,-x,-y,z);
	MathUtil::RotateZ(pt3d_mid,6,degree);
	MathUtil::Translate(pt3d_mid,6,x,y,z);


	//������
	MathUtil::Translate(pt3d_rear_wheel,2,-x,-y,z);
	MathUtil::RotateZ(pt3d_rear_wheel,2,degree);
	MathUtil::Translate(pt3d_rear_wheel,2,x,y,z);

	//�󳵸�
	MathUtil::Translate(pt3d_rear,4,-x,-y,z);
	MathUtil::RotateZ(pt3d_rear,4,degree);
	MathUtil::Translate(pt3d_rear,4,x,y,z);

	//��̥
	m_wheel_front_left->Rotate(degree,x,y,z);
	m_wheel_front_right->Rotate(degree,x,y,z);
	m_wheel_rear_left->Rotate(degree,x,y,z);
	m_wheel_rear_right->Rotate(degree,x,y,z);
	m_wheel_front_mid->Rotate(degree,x,y,z);
	m_degree +=degree;
}
void Car::go_forward()
{
	double degree_offset = m_wheel_front_mid->m_degree - m_degree;

	if( degree_offset > -ERROR &&  degree_offset < ERROR )
	{
		Translate(m_speed * sin(m_degree * PI / 180.0),
			      m_speed * -cos(m_degree * PI / 180.0),
				  0);
	 
	}
	else
	{
		double length_of_arc= PI * m_radius / 180.0;

		if(degree_offset > 0)
			Rotate( m_speed /length_of_arc,m_rotate_center.x,m_rotate_center.y,0);
		else
			Rotate(-m_speed /length_of_arc,m_rotate_center.x,m_rotate_center.y,0);
	}
} 
void Car::go_backward()
{
	double degree_offset = m_wheel_front_mid->m_degree - m_degree;
	if( degree_offset > -ERROR &&  degree_offset < ERROR )
	{
		//Util::LOG(L"degree_offset==0 sin(m_degree * PI / 180.0)=%lf cos(m_degree * PI / 180.0)=%lf m_degree=%lf",
		//	sin(m_degree * PI / 180.0),cos(m_degree * PI / 180.0),m_degree);
		Translate(-m_speed * sin(m_degree * PI / 180.0),
			      m_speed * cos(m_degree * PI / 180.0),
				  0);

	}
	else
	{
		//Util::LOG(L"degree_offset==0 sin(m_degree * PI / 180.0)=%lf cos(m_degree * PI / 180.0)=%lf m_degree=%lf",
		//	sin(m_degree * PI / 180.0),cos(m_degree * PI / 180.0),m_degree);

		double length_of_arc= PI * m_radius / 180.0;

		if(degree_offset > 0)
			Rotate(-m_speed /length_of_arc,m_rotate_center.x,m_rotate_center.y,0);
		else
			Rotate(m_speed /length_of_arc,m_rotate_center.x,m_rotate_center.y,0);
	}
}
void Car::draw(CDC &dc)
{
	//����ǰ����
	for(int i=0;i<4;i++)
	{
	   (pt_front + i)->x = (pt3d_front+i)->x;
	   (pt_front + i)->y = (pt3d_front+i)->y;
	}
	dc.MoveTo(*(pt_front+0));
	dc.LineTo(*(pt_front+1));
	dc.LineTo(*(pt_front+2));
	dc.LineTo(*(pt_front+3));

	//����ǰ����
	for(int i=0;i<2;i++)
	{
	   (pt_front_wheel + i)->x = (pt3d_front_wheel+i)->x;
	   (pt_front_wheel + i)->y = (pt3d_front_wheel+i)->y;
	}
	dc.MoveTo(*(pt_front_wheel+0));
	dc.LineTo(*(pt_front_wheel+1));

	//���Ƴ���+����
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

	//���ƺ�����
	for(int i=0;i<2;i++)
	{
	   (pt_rear_wheel + i)->x = (pt3d_rear_wheel+i)->x;
	   (pt_rear_wheel + i)->y = (pt3d_rear_wheel+i)->y;
	}
	dc.MoveTo(*(pt_rear_wheel+0));
	dc.LineTo(*(pt_rear_wheel+1));

	//����ǰ����
	for(int i=0;i<4;i++)
	{
	   (pt_rear + i)->x = (pt3d_rear+i)->x;
	   (pt_rear + i)->y = (pt3d_rear+i)->y;
	}
	dc.MoveTo(*(pt_rear+0));
	dc.LineTo(*(pt_rear+1));
	dc.LineTo(*(pt_rear+2));
	dc.LineTo(*(pt_rear+3));

	//���Ƴ���
	m_wheel_front_left->draw(dc);
	m_wheel_front_right->draw(dc);
	m_wheel_rear_left->draw(dc);
	m_wheel_rear_right->draw(dc);

	dc.MoveTo(m_wheel_front_left->getStickOutsidePosition());
	dc.LineTo(m_wheel_front_right->getStickOutsidePosition());

	//m_wheel_front_mid->draw(dc);
	if(!m_show_guide_line) return;

	
	
	CPen pen;
	CBrush br;
	br.CreateStockObject(NULL_BRUSH);//����͸��
	pen.CreatePen(PS_DOT,1,RGB(0XFF,0X1F,0XFF));//PS_DOT
	CPen* pOldPen=dc.SelectObject(&pen);
	CBrush* pOldBrush =dc.SelectObject(&br);

	if(TRUE == m_show_guide_line[0])
	{
	//��Բ��
	int width_of_pixel=5;
	dc.Ellipse(m_rotate_center.x - width_of_pixel,m_rotate_center.y - width_of_pixel,
				m_rotate_center.x + width_of_pixel,m_rotate_center.y + width_of_pixel);
	}
	double degree_offset_mid = m_wheel_front_mid->m_degree - m_degree;
	//Util::LOG(L"draw left degree = %lf  right degree = %lf degree=%lf degree_offset_left=%lf",m_wheel_front_left->m_degree,m_wheel_front_right->m_degree,m_degree,degree_offset_left);
	
	if(degree_offset_mid>0+ERROR) //ǰ����Գ���ƫ��
	{
		if(TRUE == m_show_guide_line[1])
		{
		//����Ȧ
	    double radius_outside = MathUtil::GetDistance(*(pt3d_front+1),m_rotate_center);
		dc.Ellipse(m_rotate_center.x - radius_outside,m_rotate_center.y - radius_outside,
				m_rotate_center.x + radius_outside,m_rotate_center.y + radius_outside);
		}
		if(TRUE == m_show_guide_line[2])
		{
		//����ǰ��Ȧ
	    double radius_front_wheel = MathUtil::GetDistance(*(pt3d_front_wheel+0),m_rotate_center);
		dc.Ellipse(m_rotate_center.x - radius_front_wheel,m_rotate_center.y - radius_front_wheel,
				m_rotate_center.x + radius_front_wheel,m_rotate_center.y + radius_front_wheel);
		}
		if(TRUE ==m_show_guide_line[3])
		{
		//�������Ȧ
	    double radius_rear_wheel = MathUtil::GetDistance(*(pt3d_rear_wheel+0),m_rotate_center);
		dc.Ellipse(m_rotate_center.x - radius_rear_wheel,m_rotate_center.y - radius_rear_wheel,
				m_rotate_center.x + radius_rear_wheel,m_rotate_center.y + radius_rear_wheel);
		}
		if(TRUE ==m_show_guide_line[4])
		{
		//����ǰ��Ȧ
	    double radius_front_wheel = MathUtil::GetDistance(*(pt3d_front_wheel+1),m_rotate_center);
		dc.Ellipse(m_rotate_center.x - radius_front_wheel,m_rotate_center.y - radius_front_wheel,
				m_rotate_center.x + radius_front_wheel,m_rotate_center.y + radius_front_wheel);
		}
		if(TRUE == m_show_guide_line[0])
		{
		//���뾶
		dc.MoveTo((pt3d_rear_wheel+1)->x,(pt3d_rear_wheel+1)->y);
		dc.LineTo(m_rotate_center.x,m_rotate_center.y);
		}
	}
	else if(degree_offset_mid<0-ERROR)//ǰ����Գ���ƫ��
	{
		if(TRUE == m_show_guide_line[1])
		{
		//����Ȧ
		double radius_outside = MathUtil::GetDistance(*(pt3d_front+2),m_rotate_center);
		dc.Ellipse(m_rotate_center.x - radius_outside,m_rotate_center.y - radius_outside,
			    m_rotate_center.x + radius_outside,m_rotate_center.y + radius_outside);
		}
		if(TRUE == m_show_guide_line[2])
		{
		//����ǰ��Ȧ
	    double radius_front_wheel = MathUtil::GetDistance(*(pt3d_front_wheel+1),m_rotate_center);
		dc.Ellipse(m_rotate_center.x - radius_front_wheel,m_rotate_center.y - radius_front_wheel,
				m_rotate_center.x + radius_front_wheel,m_rotate_center.y + radius_front_wheel);
		}
		if(TRUE == m_show_guide_line[3])
		{
		//�������Ȧ
	    double radius_rear_wheel = MathUtil::GetDistance(*(pt3d_rear_wheel+1),m_rotate_center);
		dc.Ellipse(m_rotate_center.x - radius_rear_wheel,m_rotate_center.y - radius_rear_wheel,
				m_rotate_center.x + radius_rear_wheel,m_rotate_center.y + radius_rear_wheel);
		}
		if(TRUE ==m_show_guide_line[4])
		{
		//����ǰ��Ȧ
	    double radius_front_wheel = MathUtil::GetDistance(*(pt3d_front_wheel+0),m_rotate_center);
		dc.Ellipse(m_rotate_center.x - radius_front_wheel,m_rotate_center.y - radius_front_wheel,
				m_rotate_center.x + radius_front_wheel,m_rotate_center.y + radius_front_wheel);
		}
		if(TRUE == m_show_guide_line[0])
		{
		//���뾶
		dc.MoveTo((pt3d_rear_wheel+0)->x,(pt3d_rear_wheel+0)->y);
		dc.LineTo(m_rotate_center.x,m_rotate_center.y);
		}
	}
	if(TRUE == m_show_guide_line[0] && degree_offset_mid != 0)
	{
	    //���ں���Ȧ
		double m_radius_tmp =m_radius - MathUtil::GetDistance(*(pt3d_rear_wheel+0),*(pt3d_rear_wheel+1))/2;
		dc.Ellipse(m_rotate_center.x - m_radius_tmp,m_rotate_center.y - m_radius_tmp,
				m_rotate_center.x + m_radius_tmp,m_rotate_center.y + m_radius_tmp);
	}
	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);
}

double Car::getLeftWheelDegree() const
{
	return  m_wheel_front_left->m_degree - this->m_degree;
}
double Car::getRightWheelDegree() const
{
	return  m_wheel_front_right->m_degree - this->m_degree;
}
double Car::getMidWheelDegree() const
{
	return  m_wheel_front_mid->m_degree - this->m_degree;
}
void Car::speedUp()
{
	++m_speed;
}
void Car::speedDown()
{
	if(m_speed>1) --m_speed;
}
int Car::getSpeed() const
{
return m_speed;
}
Car::~Car(void)
{
	delete m_wheel_front_left;//��ǰ��
	delete m_wheel_front_right;//��ǰ��

	delete m_wheel_front_mid; //��ǰ��

	delete m_wheel_rear_left;//�����
	delete m_wheel_rear_right; //�Һ���

	delete []pt3d_front; //ǰ����
	delete []pt_front;

	delete []pt3d_front_wheel; //ǰ��
	delete []pt_front_wheel;

	delete []pt3d_mid; //����+����
	delete []pt_mid;

	delete []pt3d_rear_wheel; //ǰ��
	delete []pt_rear_wheel;

	delete []pt3d_rear; //�󳵸�
	delete []pt_rear;

}