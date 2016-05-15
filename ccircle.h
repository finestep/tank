#ifndef CCIRCLE_H
#define CCIRCLE_H

#include "cpointmass.h"
#include <SDL/SDL.h>

class CCircle: public CPointMass
{
public:
	const double radius;
	CCircle(double r,double m,double posx,double posy);
	~CCircle();
	static double* collideCircles(CCircle &a,CCircle &b);
	virtual void draw(SDL_Surface* scr,int r=0, int g=255, int b=0);
};

#endif // CCIRCLE_H
