#pragma once
#include "icontrol.h"
#include "MathUtil.h"
#include "Util.h"
class ControlTips :
	public IControl
{
private:
	ThreeDPoint* m_location;
	
public:
	ControlTips(void);
	virtual ~ControlTips(void);
  void setParams(double x,double y);
  void Translate(double x,double y,double z);
  void Scale(double ratio);
  void Scale(double ratio,double x,double y,double z);
  void Rotate(double degree);
  void Rotate(double degree,double x,double y,double z);
  int m_speed;
  void draw(CDC &dc);
};

