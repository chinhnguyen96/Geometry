#pragma once
#include "Shape.h"
#include <vector>
class CPolygon :public Shape
{
	std::vector<POINT> points;
public:
	void Draw(HDC hdc) const;
	void updateRegion();
	void addPoint(int,int);
	void Move(int dx, int dy);
	CPolygon();
};