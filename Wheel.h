#pragma once
#include "IControl.h"
#include "MathUtil.h"
class Wheel :
	public IControl
{
public:
	Wheel(int x,int y,double ratio);
	void setParams(int x,int y,double m_fWheel_diameter);
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
	CPoint* pt;
	ThreeDPoint* pt3d;
	int degree;
	double m_fWheel_diameter;
};

