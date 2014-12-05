#pragma once
#include "icontrol.h"
#include "MathUtil.h"
class SteeringWheel :
	public IControl
{

private:
	ThreeDPoint* m_pt3d;
	CPoint* m_pt;
	double m_radius;
public:
	SteeringWheel(void);
	virtual ~SteeringWheel(void);
 
  void setParams(double x,double y,double radius);
  void Translate(double x,double y,double z);
  void Scale(double ratio);
  void Scale(double ratio,double x,double y,double z);
  void Rotate(double degree);
  void Rotate(double degree,double x,double y,double z);
  void draw(CDC &dc);	
  
  double m_degree_wheel_left;
  double m_degree_wheel_right;
  double m_degree_steering_wheel;  
};

