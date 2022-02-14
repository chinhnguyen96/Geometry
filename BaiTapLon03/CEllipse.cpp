#include "pch.h"
#include "CEllipse.h"

void CEllipse::Draw(HDC hdc) const
{
	Ellipse(hdc, UL.getX(), UL.getY(), BR.getX(), BR.getY());
}
void CEllipse::updateRegion() {
	DeleteObject(region);
	region = CreateEllipticRgn(UL.getX(), UL.getY(), BR.getX(), BR.getY());
}