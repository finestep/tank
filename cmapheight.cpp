#include "cmapheight.h"

#include <stdlib.h>
#include <math.h>

CMapHeight::CMapHeight(Uint16 w,Uint8 rx,Uint8 ry): width(w), resx(rx), resy(ry)
{
	IMap::friction=3;
	IMap::globalAcc=30;
	data = (Uint8*)malloc(sizeof(Uint8)*width);
	for(int i=0;i<width;i++) {
		data[i]=0;
	}
}

CMapHeight::~CMapHeight()
{
	free(data);
}

void CMapHeight::draw(SDL_Surface* scr)
{
	SDL_Rect r;
	for(int i=0;i<width;i+=resx) {
		r.x=i*resx;
		r.y=480-resy*data[i];
		r.w=resx;
		r.h=resy*data[i];
		SDL_FillRect(scr,&r,SDL_MapRGB(scr->format,110,30,30));
	}
}

double* CMapHeight::penetration(double x, double y) {
	double* ret = new double[2];
	ret[0]=0;
	ret[1]=0;
	int n = x/resx;
	double py = 480-y;
	if(n<0 || n>=width) return ret;
	if(py>resy*data[n]) return ret;
	
	
	double totalx=0;
	double totaly=0;
	for(int ix=-10;ix<11;ix++)
		for(int iy=-10;iy<11;iy++) {
			int in = ( x+ix*resx )/resx;
			if(in<0) in=0;
			if(in>=width) in=width-1;
			if(data[in]>py/resy+iy) {
				totalx+=ix*resx;
				totaly+=iy*resy;
			}

		}
	if(totalx==0&&totaly==0) {
		ret[1]=resy*data[n]-py;
		return ret;
	}
	double dist=sqrt(totalx*totalx+totaly*totaly);
	
	double dx=totalx/dist;
	double dy=-totaly/dist;

	double depth=50;
	for(double i=0;i<depth;i+=0.1) {
		int in = ( (x-i*dx)*resx )/resx;
		if(in<0) in=0;
		if(in>=width) in=width-1;
		if(data[in]<(py+dy*i)/resy) {
			depth=i;
			break;
		}
	}
	ret[0]=dx*depth;
	ret[1]=dy*depth;
	//ret[1]=resy*data[n]-py;
	return ret;
	
}

double* CMapHeight::spring(double x, double y) {
	double* ret = new double[2];
	ret[0]=170; //k
	ret[1]=160; //b
	return ret;
}
