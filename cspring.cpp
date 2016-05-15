#include "cspring.h"
#include <math.h>
#include "util.h"

CSpring::CSpring(CPointMass &a,CPointMass &b,double k,double damp,double len,bool rope):
point1(a), point2(b), k(k), damping(damp), length(len), loose(rope)
{
	if(length<=0) {
		length=sqrt(((a).posx-(b).posx)*((a).posx-(b).posx)+((a).posy-(b).posy)*((a).posy-(b).posy))+length;
	}
}

CSpring::~CSpring()
{
}

void CSpring::update(double dt) {
	double dx = point2.posx-point1.posx;
	double dy = point2.posy-point1.posy;
	double dist = sqrt(dx*dx+dy*dy);
	if(loose && dist<length) return;
	double d = (dist-length)/dist;
	
	double vx = point2.velx-point1.velx;
	double vy = point2.vely-point1.vely;
	
	double fx = k*d*dx+damping*vx;
	double fy = k*d*dy+damping*vy;
	point1.accx+=fx/point1.mass;
	point1.accy+=fy/point1.mass;
	
	point2.accx-=fx/point2.mass;
	point2.accy-=fy/point2.mass;
}

void CSpring::draw(SDL_Surface* scr,int r, int g, int b) {
	drawLine(scr,point1.posx,point1.posy,point2.posx,point2.posy,r,g,b);
}