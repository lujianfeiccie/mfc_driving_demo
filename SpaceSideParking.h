#pragma once
#include "icontrol.h"
#include "ControlTips.h"
#include "MathUtil.h"
#include "Car.h"
class SpaceSideParking :
	public IControl
{
private:
	ThreeDPoint *m_pt3d;
	CPoint *m_pt;
	ControlTips *m_tips;
public:
	SpaceSideParking(void);
	~SpaceSideParking(void);
  void setParams(double x,double y);
  void setCar(const Car *car);
  void Translate(double x,double y,double z);
  void Scale(double ratio);
  void Scale(double ratio,double x,double y,double z);
  void Rotate(double degree);
  void Rotate(double degree,double x,double y,double z);
  void draw(CDC &dc);
};

