#pragma once
#include "icontrol.h"
#include "ControlTips.h"
#include "MathUtil.h"
#include "Car.h"
#include "IControlSpace.h"
class SpaceSideParking :
	public IControlSpace
{
private:
	ThreeDPoint *m_pt3d;
	CPoint *m_pt;
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

  void setSpeed(int speed);
};

