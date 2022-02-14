#pragma once
#include"Shape.h"
class CTriangle:public Shape
{
public:
	CTriangle() {};
	CTriangle(Point, Point);
	void Draw(HDC) const;
	void updateRegion();
};