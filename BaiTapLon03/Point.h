#pragma once
#include"framework.h"
class Point
{
	int x, y;
public:
	void setX(int xx) { x = xx; };
	void setY(int yy) { y = yy; };
	int getX() const;
	int getY() const;
	void move(int dx, int dy){x += dx;y += dy;};
	Point()
	{
		x = 0;
		y = 0;
	};
	Point(int xx, int yy) {
		x = xx;
		y = yy;
	}
	~Point();
};

