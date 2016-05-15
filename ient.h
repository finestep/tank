#ifndef IENT_H
#define IENT_H

#include <SDL/SDL.h>

#include "imap.h"
#include "ccircle.h"
#include "entman.h"

class EntMan;

class IEnt {
public:
	virtual bool update(double dt,EntMan* man)=0;
	virtual void acc(double ax,double ay)=0;
	virtual void draw(SDL_Surface* scr)=0;
	virtual void mapCollide(IMap &map)=0;
	virtual CCircle** getCircles(int &count)=0;
	virtual void collide(IEnt &ent)=0;
};

#endif // IENT_H