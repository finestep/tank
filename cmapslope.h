#pragma once

#include "imap.h"

class CMapSlope: public IMap {
	const double slope;
public:
	CMapSlope(double k);
	virtual double* penetration(double x,double y);
	virtual double* spring(double x,double y);
	virtual void draw(SDL_Surface* scr);
	virtual Uint8 get(int x) {
		return slope*x-480;
		}
	virtual bool set(double x,double y) {
		return false;
	}
};