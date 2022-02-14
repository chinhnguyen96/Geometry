#include "pch.h"
#include "CRectangle.h"

void CRectangle::Draw(HDC hdc) const
{
	Rectangle(hdc, UL.getX(), UL.getY(), BR.getX(), BR.getY());
}

void CRectangle::updateRegion()
{
	DeleteObject(region);
	region = CreateRectRgn(UL.getX(), UL.getY(), BR.getX(), BR.getY());
}

CRectangle::CRectangle()
{
	region = CreateRectRgn(UL.getX(), UL.getY(), BR.getX(), BR.getY());
}

CRectangle::CRectangle(Point ul, Point br)
{
	UL = ul;
	BR = br;
	region = CreateRectRgn(UL.getX(), UL.getY(), BR.getX(), BR.getY());
}
