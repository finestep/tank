#pragma once

#include <SDL/SDL.h>


inline void drawLine(SDL_Surface* scr,int x1,int y1,int x2,int y2,int r=255,int g=0,int b=0) {
	double dx=x2-x1;
	double dy=y2-y1;
	for(double i=0;i<1;i+=0.033)
			{ 
				SDL_Rect rect;
				rect.w=1;
				rect.h=1;
				rect.x=x1+i*dx;
				rect.y=y1+i*dy;
				SDL_FillRect(scr,&rect,SDL_MapRGB(scr->format,r,g,b));
			}
}

void inline drawLineRel(SDL_Surface* scr,int x1,int y1,int x2,int y2,int r=255,int g=0,int b=0) {
	drawLine(scr,x1,y1,x1+x2,y1+y2,r,g,b);
}