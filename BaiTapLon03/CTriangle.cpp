#include "pch.h"
#include "CTriangle.h"

CTriangle::CTriangle(Point ul, Point br)
{
	UL = ul;
	BR = br;
}

void CTriangle::Draw(HDC hdc) const
{
	POINT apt[] = 
	{ {(UL.getX() + BR.getX()) / 2,UL.getY()},
		{UL.getX(),BR.getY()},
		{BR.getX(),BR.getY()}
	};
	Polygon(hdc, apt, 3);
}

void CTriangle::updateRegion()
{
	POINT apt[] =
	{ {(UL.getX() + BR.getX()) / 2,UL.getY()},
		{UL.getX(),BR.getY()},
		{BR.getX(),BR.getY()}
	};
	DeleteObject(region);
	region = CreatePolygonRgn(apt, 3, WINDING);
}
