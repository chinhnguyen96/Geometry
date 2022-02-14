#pragma once
#include"Shape.h"
class CRectangle:public Shape
{
public:
	virtual void Draw(HDC hdc) const;
	CRectangle();
	CRectangle(Point,Point);
	virtual void updateRegion();
};

