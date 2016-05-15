#ifndef CMAPHEIGHT_H
#define CMAPHEIGHT_H

#include "imap.h" // Base class: IMap
#include <SDL/SDL.h>

class CMapHeight : public IMap {
	const int width;
	const int resx; //width of one heightline
	const int resy; //height of one unit of heightline
	Uint8* data;
public:
	CMapHeight(Uint16 w,Uint8 rx,Uint8 ry);
	~CMapHeight();

	virtual void draw(SDL_Surface* scr);
	virtual double* penetration(double x, double y);
	virtual double* spring(double x, double y);
	inline Uint8 get(double x) {
		int n=x/resx;
		if(n<0) n=0;
		if(n>=width) n=width-1; 
		return 480-data[n]*resy;
		}
	inline bool set(double x, double y) {
		int n=x/resx;
		if(y>480) y=480;
		int c=(480-y)/resy;
		if(c>255) c=255;
		if(n>=0&&n<width) {
			data[n]=c;
			return true;
		}
		return false;
	}
};

#endif // CMAPHEIGHT_H
