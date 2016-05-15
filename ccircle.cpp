#include "ccircle.h"

#include <math.h>
#include <SDL/SDL.h>

CCircle::CCircle(double r,double m,double px=0,double py=0): CPointMass(m,px,py),radius(r)
{
}

CCircle::~CCircle()
{
}

void CCircle::draw(SDL_Surface* scr,int r, int g, int b) {
	static double a = 2;
	static double c = 2/sqrt(2);
	double k = radius*.5*a;
	double j = radius*.5*c;
	SDL_Rect rect;
	rect.x=posx-k;
	rect.y=posy-j;
	rect.w=k*2;
	rect.h=j*2;
	SDL_FillRect(scr,&rect,SDL_MapRGB(scr->format,r,g,b));
	rect.x=posx-j;
	rect.y=posy-k;
	rect.w=j*2;
	rect.h=k*2;
	SDL_FillRect(scr,&rect,SDL_MapRGB(scr->format,r,g,b));
}

double* CCircle::collideCircles(CCircle &a, CCircle &b) {
	double* ret = new double[2];
	ret[0]=0;
	ret[1]=0;
	double dx = b.posx-a.posx;
	double dy = b.posy-a.posy;
	if(fabs(dx)>a.radius+b.radius||fabs(dy)>a.radius+b.radius) return ret;
	double dist = sqrt(dx*dx+dy*dy);
	double dr = dist-a.radius-b.radius;
	if(dr>0) return ret;
	double nx = dx/dist;
	double ny = dy/dist;
	ret[0] = nx*(dr);
	ret[1] = ny*(dr);
	return ret;
}