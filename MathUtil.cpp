#include "StdAfx.h"
#include "MathUtil.h"
#include "Util.h"

MathUtil::MathUtil(void)
{
}


MathUtil::~MathUtil(void)
{
}
void MathUtil::MultipleMarix(double pt[1][4],double matrix[4][4],double result[1][4])
{
 for(int i=0;i<4;i++) result[0][i] = 0;

 for(int i=0; i<1;i++)
  for(int j=0;j<4;j++)
   for(int k=0;k<4;k++)
    result[i][j] += pt[i][k] * matrix[k][j];
}
 void MathUtil::PointToMarix(ThreeDPoint pt,double m[1][4])
 {
	m[0][0] = pt.x;	m[0][1] = pt.y;	m[0][2] = pt.z;	m[0][3] = 1;
 }
 void MathUtil::MarixToPoint(double m[1][4],ThreeDPoint &pt)
 {
	pt.x = m[0][0]; pt.y = m[0][1]; pt.z = m[0][2];
 }
 void MathUtil::Translate(ThreeDPoint pt[],int size,double x,double y,double z)
 {
	double (*temp)[4] = new double[size][4];
	double result[1][4];
	double moveMarix[4][4] = 
	{
	 {1,0,0,0},
	 {0,1,0,0},
	 {0,0,1,0},
	 {x,y,z,1}
	};

	 for(int i=0;i<size;i++)
	 {
	   PointToMarix(  pt[i],temp+i);
	   MultipleMarix(temp+i,moveMarix,result);
	   MarixToPoint( result,pt[i]);
	 }
	 delete []temp;
 }

  void MathUtil::RotateX(ThreeDPoint pt[],int size,double degree)
  {
    double (*temp)[4] = new double[size][4];
	double result[1][4];
	double moveMarix[4][4] = 
	{
	 {1,0					  ,0         		    ,0},
	 {0,cos(degree * PI / 180.0) ,sin(degree * PI / 180.0),0},
	 {0,-sin(degree * PI / 180.0),cos(degree * PI / 180.0),0},
	 {0,0					  ,0				    ,1}
	};
	 for(int i=0;i<size;i++)
	 {
	   PointToMarix(  pt[i],temp+i);
	   MultipleMarix(temp+i,moveMarix,result);
	   MarixToPoint( result,pt[i]);
	 }

	 delete []temp;
  }
  void MathUtil::RotateY(ThreeDPoint pt[],int size,double degree)
  {
    double (*temp)[4] = new double[size][4];
	double result[1][4];
	double moveMarix[4][4] = 
	{
	 {cos(degree * PI / 180),0,-sin(degree * PI / 180),0},
	 {0					   ,1,0						,0},
	 {sin(degree * PI / 180),0,cos(degree * PI / 180) ,0},
	 {0                    ,0,0				        ,1}
	};

	 for(int i=0;i<size;i++)
	 {
	   PointToMarix(  pt[i],temp+i);
	   MultipleMarix(temp+i,moveMarix,result);
	   MarixToPoint( result,pt[i]);
	 }

	 delete []temp;
  }
  void MathUtil::RotateZ(ThreeDPoint pt[],int size,double degree)
  {
	double (*temp)[4] = new double[size][4];
	        
	double result[1][4];
	double moveMarix[4][4] = 
	{
	 {cos(degree * PI / 180), sin(degree * PI / 180), 0,0},
	 {-sin(degree * PI / 180),cos(degree * PI / 180), 1,0},
	 {0,0,1,0},
	 {0,0,0,1}
	};

	 for(int i=0;i<size;i++)
	 {
	   PointToMarix(  pt[i],temp+i);
	   MultipleMarix(temp+i,moveMarix,result);
	   MarixToPoint( result,pt[i]);
	 }

	 delete []temp;
  }

  void MathUtil::Scale(ThreeDPoint pt[],int size,double ratio)
  {
    double (*temp)[4] = new double[size][4];
	double result[1][4];
	double moveMarix[4][4] = 
	{
	 {ratio,0,0,0},
	 {0,ratio,0,0},
	 {0,0,ratio,0},
	 {0,0,	  0,1}
	};

	 for(int i=0;i<size;i++)
	 {
	   PointToMarix(  pt[i],temp+i);
	   MultipleMarix(temp+i,moveMarix,result);
	   MarixToPoint( result,pt[i]);
	 }

	 delete []temp;
  }