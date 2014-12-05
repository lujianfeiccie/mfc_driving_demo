#pragma once
#include "IControl.h"
#include "Car.h"
#include "MathUtil.h"
#include "ControlTips.h"
#include "IControlSpace.h"
class SpaceTurnRight : public IControlSpace
{
public:
   SpaceTurnRight(void);
   virtual ~SpaceTurnRight(void);
  void setParams(double x,double y);	
  void setCar(const Car *car);
  void Translate(double x,double y,double z);
  void Scale(double ratio);
  void Scale(double ratio,double x,double y,double z);
  void Rotate(double degree);
  void Rotate(double degree,double x,double y,double z);
  void draw(CDC &dc);	
private:
	ThreeDPoint* m_pt3d;
	CPoint* m_pt;
	BOOL m_bFirstDraw;
};

