#include "cshell.h"

#include <math.h>

#include "cexplosion.h"

CShell::CShell(double px,double py,double vx,double vy, double r)
{
	circle = new CCircle(3,r,px,py);
	circle->velx=vx;
	circle->vely=vy;
}

CShell::~CShell()
{
	delete circle;
}

bool CShell::update(double dt,EntMan* man) {
	circle->update(dt);
	double vel = sqrt(circle->velx*circle->velx+circle->vely*circle->vely);
	if(vel<50||vel>3010) {
		IEnt* ent = new CExplosion(circle->posx,circle->posy,8,700/dt);
		man->addEnt(ent);
		return true;
	}
	return false;
}
void CShell::acc(double ax,double ay) {
	circle->accx+=ax;
	circle->accy+=ay;
}
void CShell::draw(SDL_Surface* scr) {
	circle->draw(scr);
}
void CShell::mapCollide(IMap &map) {
	double* d = map.penetration(circle->posx,circle->posy);

	double dx = d[0];
	double dy = d[1];
	double depth = sqrt(dx*dx+dy*dy);
	if(depth>0.0000001) {
		circle->velx/=(1+depth*1.5);
		circle->vely/=(1+depth*1.5);
		}
	delete d;
}
void CShell::collide(IEnt &ent) {
	int count=0;
	CCircle** c=ent.getCircles(count);
	double* d = new double[2];
	for(int j=0;j<count;j++) {
		d = CCircle::collideCircles(*circle,*c[j]);

		double dx=d[0];
		double dy=d[1];
		double depth = sqrt(dx*dx+dy*dy);
		if(depth>0) {
/*			static double k = 150;
			static double b = 170;
			

			double nx = -dx/depth;
			double ny = -dy/depth;
			double dp = nx*(circle->velx-c[j]->velx)+ny*(circle->vely-c[j]->vely);
			
			double fx = nx*k*depth;
			double fy = ny*k*depth;
			double bx = b*nx*dp;
			double by = b*ny*dp;
			
			circle->force(fx-bx,fy-by);
			
			c[j]->force((bx-fx),(by-fy)); */
			circle->velx=0;
			circle->vely=0;
			}
	}
	delete d;
}