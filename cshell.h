#ifndef CSHELL_H
#define CSHELL_H


#include <SDL/SDL.h>

#include "ient.h"
#include "ccircle.h"


class CShell: public IEnt
{
	CCircle* circle;
public:
	CShell(double px,double py,double vx,double vy,double r=3);
	~CShell();
	bool update(double dt,EntMan* man);
	virtual void collide(IEnt& ent);
	inline virtual CCircle** getCircles(int &count) {
		count=1;
		return &circle;
	}
	void acc(double ax,double ay);
	void draw(SDL_Surface* scr);
	void mapCollide(IMap &map);
};

#endif // CSHELL_H
