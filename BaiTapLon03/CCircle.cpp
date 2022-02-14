#include "pch.h"
#include "CCircle.h"

void CCircle::UpdateBR(Point br)
{
	//Force circle
	int dx = br.getX()- UL.getX();
	int dy = br.getY()- UL.getY();
	if (abs(dx) > abs(dy)) {
		if (br.getX() < UL.getX())
			br.setX(UL.getX() - abs(dy));
		else
			br.setX(UL.getX() + abs(dy));
	}
	else {
		if (br.getY() < UL.getY())
			br.setY(UL.getY() - abs(dx));
		else
			br.setY(UL.getY() + abs(dx));
	}
	BR = br;
	updateRegion();
}
