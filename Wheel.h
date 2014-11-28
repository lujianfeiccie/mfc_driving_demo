#pragma once
#include "IControl.h"
#include "MathUtil.h"
class Wheel :
	public IControl
{
public:
	Wheel();
	void setParams(int x,int y,double car_cx,double car_cy,double ratio,double m_fWheel_diameter);
	~Wheel(void);

  //Interface

  void draw(CPaintDC &dc);

  //self

    void go_foward();

    void go_backward();

	void turn_left();

	void turn_right();

	void Translate(double x,double y,double z);
	void Scale(double ratio);
	void ScaleCar(double ratio);
	void Rotate(double degree);
	void Rotate(double degree,double x,double y,double z);
	CPoint* pt;
	ThreeDPoint* pt3d;
	double m_fWheel_diameter;
	double m_car_cx;
	double m_car_cy;
};

