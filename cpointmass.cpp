#include "cpointmass.h"



CPointMass::CPointMass(double m, double x,double y, double vx,double vy,bool anch):
mass(m), posx(x),posy(y),velx(vx),vely(vy),accx(0),accy(0),fixed(anch)
{
}
CPointMass::CPointMass(bool anch,double x,double y):
mass(1), posx(x),posy(y),velx(0),vely(0),accx(0),accy(0),fixed(anch)
{
}
CPointMass::~CPointMass()
{
}

void CPointMass::update(double dt) {

	if(fixed) return;
	velx+=accx*dt;
	vely+=accy*dt;
	
	posx+=velx*dt;
	posy+=vely*dt;
	
	accx=0;
	accy=0;
}

void CPointMass::draw(SDL_Surface* scr,int r, int g, int b) {
	SDL_Rect rect;
	rect.x=posx-1;
	rect.y=posy-1;
	rect.w=3;
	rect.h=3;
	SDL_FillRect(scr,&rect,SDL_MapRGB(scr->format,r,g,b));
}