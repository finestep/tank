#include "cexplosion.h"

#include <math.h>

CExplosion::CExplosion(double px,double py,double radius,double power):
 radius(radius), power(power), life(0), lifeTime(0.3)
{
	circle = new CCircle(radius,2000000,px,py);
}

CExplosion::~CExplosion()
{
	delete circle;
}


bool CExplosion::update(double dt,EntMan* man) {
	circle->velx=0;
	circle->vely=0;
	circle->update(dt);
	life+=dt;
	return life>lifeTime;
}

void CExplosion::draw(SDL_Surface* scr) {
	circle->draw(scr,220,170,20);
}
void CExplosion::mapCollide(IMap &map) {
	double y;
	for(double x=-radius;x<radius;x+=1) {
		y=circle->posy+sqrt(radius*radius-x*x);
		if(map.get(circle->posx+x)<480-y)
		map.set(circle->posx+x,y);
	}
}
void CExplosion::collide(IEnt &ent) {
	int count=0;
	CCircle** c=ent.getCircles(count);
	double* d = new double[2];
	for(int j=0;j<count;j++) {
		d = CCircle::collideCircles(*circle,*c[j]);

		double dx=d[0];
		double dy=d[1];
		double depth = sqrt(dx*dx+dy*dy);
		if(depth>0) {

			c[j]->force(-dx*power/(1+depth*depth),-dy*power/(1+depth*depth));
			}
	}
	delete d;
}