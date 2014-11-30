#pragma once
#include "IControl.h"
#include "Car.h"
class SpaceTurnRight : public IControl
{
public:
   SpaceTurnRight(void);
   ~SpaceTurnRight(void);
  void setParams(double x,double y);	
  void setCar(Car *car);
  void Translate(double x,double y,double z);
  void Scale(double ratio);
  void Scale(double ratio,double x,double y,double z);
  void Rotate(double degree);
  void Rotate(double degree,double x,double y,double z);
  void draw(CPaintDC &dc);	
private:
	Car *car;
};

