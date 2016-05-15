#ifndef CSPRING_H
#define CSPRING_H

#include "cpointmass.h"
#include <SDL/SDL.h>

class CSpring
{
	CPointMass & point1;
	CPointMass & point2;

public:
	double k;
	double length;
	double damping;
	bool loose;
	CSpring(CPointMass &a,CPointMass &b,double k,double damping=0,double len=0,bool rope=false);
	~CSpring();
	void update(double dt);
	virtual void draw(SDL_Surface* scr,int r=0, int g=0, int b=255);
};

#endif // CSPRING_H
