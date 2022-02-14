#pragma once
#include"Shape.h"
class CEllipse:public Shape
{
public:
	virtual void Draw(HDC hdc) const;
	virtual void updateRegion();
	CEllipse() 
	{
		region = CreateEllipticRgn(UL.getX(), UL.getY(), BR.getX(), BR.getY());
	};
	
	CEllipse(Point T, int xr, int yr)
	{
		UL.setX(T.getX() - xr);
		UL.setY(T.getY() - yr);
		BR.setX(T.getX() + xr);
		BR.setY(T.getY() + yr);
		region = CreateEllipticRgn(UL.getX(), UL.getY(), BR.getX(), BR.getY());
	}
};

