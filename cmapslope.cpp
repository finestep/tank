#include "cmapslope.h"
#include <math.h>

#include <SDL/SDL.h>

CMapSlope::CMapSlope(double k): slope(k)
{
	friction=1;
	globalAcc=10;
}

double* CMapSlope::penetration(double x,double y) {
	double* ret = new double[2];
	ret[0]=0;
	ret[1]=0;
	if(y>480-x*slope) {
		static double d = sqrt(slope*slope+1);
		double dist = fabs(slope*x+y-480)/d;
		ret[0]=slope/d*dist;
		ret[1]=1/d*dist;
	}
	return ret;
}
double* CMapSlope::spring(double x,double y) {
	double* ret = new double[2];
	ret[0]=25; //k
	ret[1]=15; //b
	return ret;
}
void CMapSlope::draw(SDL_Surface* scr) {
	SDL_Rect r;
	for(int i=0;i<640;i++) {
			r.w=640;
			r.h=2;
			r.x=i;
			r.y=480-i*slope;
			SDL_FillRect(scr,&r,SDL_MapRGB(scr->format,110,40,40));
		}
}