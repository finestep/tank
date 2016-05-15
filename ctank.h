#ifndef CTANK_H
#define CTANK_H

#include <SDL/SDL.h>

#include "ient.h"

#include "cpointmass.h"
#include "cspring.h"
#include "imap.h"

class CTank: public IEnt
{
	CPointMass* points[3];
	CCircle* circles[3];
	CSpring* springs[11];
	bool grounded[3];
	double engine;
	const double engineTorque;
	const double engineFriction;
	
	double lastAccx;
	double lastAccy;
	
	double mapForcex;
	double mapForcey;
	
	Uint8* controls;
	
	double angle;
	const double aimSpeed;
	double reload;
	const double reloadTime;
public:
	const float scale;
	CTank(double posx,double posy,Uint8* c=NULL,float scale=2);
	~CTank();
	bool update(double dt,EntMan* man);
	void acc(double ax,double ay);
	void draw(SDL_Surface* scr);
	void mapCollide(IMap &map);
	inline CPointMass** getPoints() {
		return points;
	}
	inline CSpring** getSprings() {
		return springs;
	}
	void collide(IEnt &ent);
	inline virtual CCircle** getCircles(int &count) {
		count=3;
		return circles;
	}
};

#endif // CTANK_H
