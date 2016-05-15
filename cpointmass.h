#ifndef CPOINTMASS_H
#define CPOINTMASS_H

#include <SDL/SDL.h>

class CPointMass
{
public:
	const double mass;
	double posx,posy;
	double velx,vely;
	double accx,accy;
	bool fixed;
	CPointMass(double m, double x=0,double y=0, double vx=0,double vy=0,bool anch=false);
	CPointMass(bool anch,double px,double py);
	~CPointMass();
	virtual void update(double dt);
	virtual void draw(SDL_Surface* scr,int r=255, int g=0, int b=0);
	virtual inline void force(double fx,double fy) {
		accx+=fx/mass;
		accy+=fy/mass;
	}
};

#endif // CPOINTMASS_H
