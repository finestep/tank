#ifndef CEXPLOSION_H
#define CEXPLOSION_H

#include "ient.h"
#include "ccircle.h"

class CExplosion: public IEnt
{
	CCircle* circle;
	const double power;
	const double radius;
	double life;
	const double lifeTime;

public:
	CExplosion(double px,double py,double radius,double power);
	~CExplosion();
	bool update(double dt,EntMan* man);
	virtual void collide(IEnt& ent);
	inline virtual CCircle** getCircles(int &count) {
		count=1;
		return &circle;
	}
	inline void acc(double ax,double ay) {};
	void draw(SDL_Surface* scr);
	void mapCollide(IMap &map);
};

#endif // CEXPLOSION_H
