#pragma once
class IControl
{
public:
	IControl(void);
	~IControl(void);

 double m_dRatio;

 double m_dX;

 double m_dY;

public:



 virtual  void draw(CPaintDC &dc)=0;

};

