#pragma once
#include "CEllipse.h"
class CCircle:public CEllipse
{
public:
	CCircle()
	{
		region = CreateEllipticRgn(UL.getX(), UL.getY(), BR.getX(), BR.getY());
	}

	CCircle(Point T, int r)
	{
		UL.setX(T.getX() - r);
		UL.setY(T.getY() - r);
		BR.setX(T.getX() + r);
		BR.setY(T.getY() + r);
		region = CreateEllipticRgn(UL.getX(), UL.getY(), BR.getX(), BR.getY());
	}
	void UpdateBR(Point);
};

