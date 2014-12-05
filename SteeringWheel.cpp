#include "StdAfx.h"
#include "SteeringWheel.h"
#include "Util.h"
#define SIZE_OF_VERTEX 9

SteeringWheel::SteeringWheel(void)
{
	m_pt3d = new ThreeDPoint[SIZE_OF_VERTEX];
	m_pt = new CPoint[SIZE_OF_VERTEX];
	m_degree = 0;
	m_degree_wheel_left = 0;
	m_degree_wheel_right = 0;
	m_degree_steering_wheel = 0;
}


SteeringWheel::~SteeringWheel(void)
{
	Util::LOG(L"~SteeringWheel");
	delete []m_pt3d;
	delete []m_pt;
}
 void SteeringWheel:: setParams(double x,double y,double radius)
 {
	  this->m_dX = x;
	  this->m_dY = y;
	  this->m_radius = radius;
	  //左边矩形
	  double width = 20;
	  (m_pt3d + 0)->x = x - radius;
	  (m_pt3d + 0)->y = y - width/2;
	  
	  (m_pt3d + 1)->x = x + radius;
	  (m_pt3d + 1)->y = (m_pt3d + 0)->y;

	  (m_pt3d + 2)->x = (m_pt3d + 1)->x;
	  (m_pt3d + 2)->y = (m_pt3d + 1)->y+width;

	  (m_pt3d + 3)->x = (m_pt3d + 2)->x - radius + width/2;
	  (m_pt3d + 3)->y =  (m_pt3d + 2)->y;

	  (m_pt3d + 4)->x = (m_pt3d + 3)->x;
	  (m_pt3d + 4)->y = (m_pt3d + 3)->y+radius-width/2;

	  (m_pt3d + 5)->x = (m_pt3d + 4)->x - width;
	  (m_pt3d + 5)->y = (m_pt3d + 4)->y;

	  (m_pt3d + 6)->x = (m_pt3d + 5)->x;
	  (m_pt3d + 6)->y = (m_pt3d + 5)->y -radius+width/2;

	  (m_pt3d + 7)->x = (m_pt3d + 0)->x;
	  (m_pt3d + 7)->y = (m_pt3d + 6)->y;

	  (m_pt3d+SIZE_OF_VERTEX-1)->x = x;
	  (m_pt3d+SIZE_OF_VERTEX-1)->y = y;
 }
  void SteeringWheel:: Translate(double x,double y,double z)
 {
	 MathUtil::Translate(m_pt3d,SIZE_OF_VERTEX,x,y,z);
	 this->m_dX = (m_pt3d+SIZE_OF_VERTEX-1)->x;
	 this->m_dY = (m_pt3d+SIZE_OF_VERTEX-1)->y;
	 Util::LOG(L" SteeringWheel:: Translate(%lf,%lf)",this->m_dX,this->m_dY);
 }
  void SteeringWheel:: Scale(double ratio)
  {
	  Scale(ratio,this->m_dX,this->m_dY,0);
  }
  void SteeringWheel:: Scale(double ratio,double x,double y,double z)
  {
	  MathUtil::Translate(m_pt3d,SIZE_OF_VERTEX,-x,-y,-z);
	  MathUtil::Scale(m_pt3d,SIZE_OF_VERTEX,ratio);
	  MathUtil::Translate(m_pt3d,SIZE_OF_VERTEX,x,y,z);
	 this->m_dX = (m_pt3d+SIZE_OF_VERTEX-1)->x;
	 this->m_dY = (m_pt3d+SIZE_OF_VERTEX-1)->y;
  }
  void SteeringWheel:: Rotate(double degree)
  {
	//  m_degree = degree;
	  Rotate(degree,this->m_dX,this->m_dY,0);
  }
  void SteeringWheel:: Rotate(double degree,double x,double y,double z)
  {
	  MathUtil::Translate(m_pt3d,SIZE_OF_VERTEX,-x,-y,-z);
	  MathUtil::RotateZ(m_pt3d,SIZE_OF_VERTEX,degree);
	  MathUtil::Translate(m_pt3d,SIZE_OF_VERTEX,x,y,z);
	 this->m_dX = (m_pt3d+SIZE_OF_VERTEX-1)->x;
	 this->m_dY = (m_pt3d+SIZE_OF_VERTEX-1)->y;
	 m_degree +=degree;
  }


void SteeringWheel:: draw(CDC &dc)
{
	for(int i=0;i<SIZE_OF_VERTEX;++i)
	{
		(m_pt+i)->x = (m_pt3d+i)->x;
		(m_pt+i)->y = (m_pt3d+i)->y;
	}

	double radius = m_radius;
	dc.Ellipse(this->m_dX - radius,this->m_dY - radius,
			   this->m_dX + radius,this->m_dY + radius);

	radius*=0.3;
	dc.Ellipse(this->m_dX - radius,this->m_dY - radius,
			   this->m_dX + radius,this->m_dY + radius);

	CPen MyPen,*OldPen;	
	MyPen.CreatePen(PS_SOLID,1,RGB(0,0,0));
	OldPen=dc.SelectObject(&MyPen);	
	CBrush MyBrush,*OldBrush;	
	MyBrush.CreateSolidBrush(RGB(0,0,0));
	OldBrush=dc.SelectObject(&MyBrush);

	dc.Polygon(m_pt,SIZE_OF_VERTEX-1);
	
	dc.SelectObject(OldPen);
	dc.SelectObject(OldBrush);

	CString tmp;
	tmp.Format(L"左前轮:%.1lf度 右前轮:%.1lf度",
		m_degree_wheel_left,m_degree_wheel_right);
 
	CFont font, *pOldFont= NULL;//定义字体对象及其指针 ，你可以根据需求选择你要的字体类型和大小
    font.CreatePointFont(120, L"楷体", &dc);
	pOldFont = dc.SelectObject(&font);

	dc.TextOutW(this->m_dX-90,this->m_dY + m_radius+30,tmp);

	tmp.Format(L"方向盘:%.1lf度≈%.1lf圈",m_degree_steering_wheel,m_degree_steering_wheel/360.0);
	dc.TextOutW(this->m_dX-90,this->m_dY - m_radius-20,tmp);

	dc.SelectObject(pOldFont);
	font.DeleteObject();
	//DrawBmp(&dc,L"F:\\work\\DrivingDemo\\DrivingDemo\\steering_wheel.bmp",this->m_degree);
}	