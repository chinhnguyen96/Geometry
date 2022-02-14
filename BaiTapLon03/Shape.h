#pragma once
#include "framework.h"
#include "Point.h"
class Shape
{
protected:
	Point UL,BR;//Diem upper-left, bottom-right
	HRGN region;//Region
public:
	virtual void Draw(HDC hdc) const = 0;
	virtual void Move(int dx, int dy);
	void Scale(double s);
	HRGN getRegion() const { return region; };
	virtual void UpdateBR(Point);//Chi update diem cuoi
	virtual void updateRegion() = 0;
};