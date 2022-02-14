#include "pch.h"
#include "CSquare.h"
#include "math.h"
void CSquare::UpdateBR(Point br)
{
	//Force square
	int dx = br.getX()- UL.getX();
	int dy = br.getY()- UL.getY();
	if (abs(dx) > abs(dy)) {//Dich chuyen br.x
		if (br.getX() < UL.getX())//br nam ben trai UL
			br.setX(UL.getX() - abs(dy));
		else//br nam ben phai UL
			br.setX(UL.getX() + abs(dy));
	}
	else {//Dich chuyen br.y
		if (br.getY() < UL.getY())//br nam phia tren UL
			br.setY(UL.getY() - abs(dx));
		else//br nam phia duoi UL
			br.setY(UL.getY() + abs(dx));
	}

	BR = br;
	updateRegion();
}
