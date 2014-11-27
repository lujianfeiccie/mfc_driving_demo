#pragma once
#include <cmath>
#define PI  3.1415926535898 

typedef struct 
{
	double x;
	double y;
	double z;
}ThreeDPoint;
class MathUtil
{
public:
	MathUtil(void);
	~MathUtil(void);
private:
   static void MultipleMarix(double pt[1][4],double matrix[4][4],double result[1][4]);
   static void PointToMarix(ThreeDPoint pt,double m[1][4]);
   static void MarixToPoint(double m[1][4],ThreeDPoint &pt);
public:
   static void Translate(ThreeDPoint pt[],int size,double x,double y,double z);
   static void RotateX(ThreeDPoint pt[],int size,double degree);
   static void RotateY(ThreeDPoint pt[],int size,double degree);
   static void RotateZ(ThreeDPoint pt[],int size,double degree);
   static void Scale(ThreeDPoint pt[],int size,double ratio);
};

