#include "pch.h"
#include "CPolygon.h"

void CPolygon::Draw(HDC hdc) const
{
	Polygon(hdc, &points[0], points.size());
}

void CPolygon::updateRegion()
{
	DeleteObject(region);
	region = CreatePolygonRgn(&points[0], points.size(), ALTERNATE);
}

void CPolygon::addPoint(int x,int y)
{
	POINT tmp;
	tmp.x = x;
	tmp.y = y;
	//tmp la vi tri con chuot
	
	if (points.size() == 0) //Diem dau tien la UL,BR
	{
		UL.setX(x);
		UL.setY(y);
		BR.setX(x);
		BR.setY(y);
	}
	else 
	{
		//Expand UL,BR to carry all the point
		if (x < UL.getX() || y < UL.getY()) 
		{
			UL = Point(x, y);
		}
		else if (x > BR.getX() || y > BR.getY()) 
		{
			BR = Point(x, y);
		}
	}
	points.push_back(tmp);
	updateRegion();
}

void CPolygon::Move(int dx, int dy)
{
	Shape::Move(dx, dy);//Move UL,BR
	//Di chuyen tung point
	for (int i = 0; i < points.size(); i++) 
	{
		points[i].x += dx;
		points[i].y += dy;
	}
}

CPolygon::CPolygon()
{
	UL = Point(-1,-1);
	BR = Point(-1,-1);
}
