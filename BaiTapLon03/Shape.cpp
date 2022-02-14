#include "pch.h"
#include "Shape.h"

void Shape::Move(int dx, int dy) 
{
	//Di chuyen shape
	UL.move(dx, dy);
	BR.move(dx, dy);

	//Di chuyen region theo shape
	OffsetRgn(region, dx, dy);
}
void Shape::Scale(double s) 
{
	int dx = (BR.getX() - UL.getX());
	int dy = (BR.getY() - UL.getY());

	if (s>0 || abs(dx) > 10 && abs(dy) > 10) //Min size
	{
		//Move dung ty le hinh
		double ratio = dx / dy;

		if(BR.getY()>UL.getY())
			BR.move(s * ratio, s);
		else
			BR.move(-s * ratio, -s);

		this->updateRegion();
	}
}
void Shape::UpdateBR(Point br)
{
	BR = br;
	updateRegion();
}
