#ifndef CMAP_H
#define CMAP_H

#include <SDL/SDL.h>

class IMap
{
public:
	double friction;
	double globalAcc;
	virtual double* penetration(double x,double y)=0;
	virtual double* spring(double x,double y)=0;
	virtual void draw(SDL_Surface* scr)=0;
	virtual Uint8 get(double x)=0;
	virtual bool set(double x,double y)=0;
};

#endif // CMAP_H
