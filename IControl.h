#pragma once
class IControl
{
public:
	IControl(void);
	~IControl(void);

 double m_dRatio;

 double m_dX;

 double m_dY;

 double m_degree;

 virtual  void draw(CDC &dc)=0;
 virtual void Translate(double x,double y,double z)=0;
 virtual void Scale(double ratio)=0;
 virtual void Scale(double ratio,double x,double y,double z)=0;
 virtual void Rotate(double degree)=0;
 virtual void Rotate(double degree,double x,double y,double z)=0;
};

