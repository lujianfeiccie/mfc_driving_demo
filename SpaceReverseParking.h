#pragma once
#include "icontrol.h"
#include "Car.h"
#include "MathUtil.h"
#include "Util.h"
#include "ControlTips.h"
#include "IControlSpace.h"
class SpaceReverseParking :
	public IControlSpace
{
private:
	ThreeDPoint *m_pt3d;
	CPoint *m_pt;	
public:
	SpaceReverseParking(void);
	~SpaceReverseParking(void);
  void setParams(double x,double y);
  void setCar(const Car *car);
  void Translate(double x,double y,double z);
  void Scale(double ratio);
  void Scale(double ratio,double x,double y,double z);
  void Rotate(double degree);
  void Rotate(double degree,double x,double y,double z);
   void draw(CDC &dc);
};

