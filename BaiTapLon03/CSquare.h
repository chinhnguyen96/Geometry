#pragma once
#include"CRectangle.h"
class CSquare:public CRectangle
{
public:
	CSquare() {};
	CSquare(Point ul, int r) {
		UL = ul;
		BR.setX(ul.getX() + r);//BR.x=ul.x+r
		BR.setY(ul.getY() + r);
		region = CreateRectRgn(UL.getX(), UL.getY(), BR.getX(), BR.getY());
	};
	void UpdateBR(Point);
};

