#include "ctank.h"

#include <math.h>
#include <SDL/SDL.h>
#include "util.h"

#include "ccircle.h"
#include "ccontroller.h"
#include "cshell.h"

CTank::CTank(double x,double y,Uint8* c,float scale):
lastAccx(0),lastAccy(0),mapForcex(0),mapForcey(0), scale(scale), controls(c),
 engine(0), engineTorque(80*scale), engineFriction(pow(0.8,1./60)),
 angle(0), aimSpeed(0.7), reload(0), reloadTime(3)
{

	CCircle* circle = new CCircle(6*scale,2*scale,x,y-2*scale);
	circles[0] = circle;
	
	circle = new CCircle(4*scale,2*scale,x-9*scale,y);
	circles[1] = circle;
	
	circle = new CCircle(4*scale,2*scale,x+9*scale,y);
	circles[2] = circle;
	

	CPointMass* point = new CPointMass(4*scale,x,y+6*scale);
	points[0] = point;

	point = new CPointMass(4*scale,x-9*scale,y+6*scale);
	points[1] = point;

	point = new CPointMass(4*scale,x+9*scale,y+6*scale);
	points[2] = point;
	
	CSpring* spring = new CSpring(*points[0],*circles[0],65*scale,32*scale);
	springs[0] = spring;
	spring = new CSpring(*points[1],*circles[1],67*scale,36*scale);
	springs[1] = spring;
	spring = new CSpring(*points[2],*circles[2],67*scale,36*scale);
	springs[3] = spring;


	spring = new CSpring(*points[1],*points[0],35*scale,35*scale);
	springs[5] = spring;
	spring = new CSpring(*points[0],*points[2],35*scale,35*scale);
	springs[6] = spring;

	spring = new CSpring(*circles[1],*circles[0],55*scale,32*scale);
	springs[7] = spring;
	spring = new CSpring(*circles[0],*circles[2],55*scale,32*scale);
	springs[8] = spring;

	spring = new CSpring(*points[1],*circles[2],62*scale,20*scale,-1);
	springs[2] = spring;

	spring = new CSpring(*points[2],*circles[1],62*scale,20*scale,-1);
	springs[4] = spring;
	
	spring = new CSpring(*circles[0],*points[1],73*scale,40*scale);
	springs[9] = spring;
	spring = new CSpring(*circles[0],*points[2],73*scale,40*scale);
	springs[10] = spring;

	grounded[0]=false;
	grounded[1]=false;
	grounded[2]=false;

}

CTank::~CTank()
{
	for(int i=0;i<3;i++) {
		delete points[i];
	}
	for(int i=0;i<3;i++) {
		delete circles[i];
	}
	for(int j=0;j<11;j++) {
		delete springs[j];
	}
}


bool CTank::update(double dt,EntMan* man) {

	if(controls!=NULL) {
		if(*controls&(Uint8)CTRL_LEFT) {
			engine+=engineTorque*dt;
		}
		if(*controls&(Uint8)CTRL_RIGHT) {
			engine-=engineTorque*dt;
		}
		if(*controls&(Uint8)CTRL_UP) {
			angle+=aimSpeed*dt;
		}
		if(*controls&(Uint8)CTRL_DOWN) {
			angle-=aimSpeed*dt;
		}
		if(angle>.5) angle=.5;
		if(angle<-.5) angle=-.5;
		if(*controls&(Uint8)CTRL_FIRE&&reload==0) {
			double a = angle*(engine>0?1:-1)+(engine>0?3.14:0);
			static double shellVel=900;
			static double shellScale=scale*0.4;
			CShell* ent = new CShell(circles[0]->posx+cos(a)*20*scale,
										-6*scale+circles[0]->posy+sin(a)*20*scale,
										circles[0]->velx+cos(a)*shellVel,circles[0]->vely+sin(a)*shellVel, shellScale);
			circles[0]->force(-cos(a)*shellVel*shellScale/dt,-sin(a)*shellVel*shellScale/dt);
			man->addEnt((IEnt*)ent);
			reload=reloadTime;
		}
	}

	engine*=engineFriction;
	
	reload-=dt;
	if(reload<0) reload=0;

	for(int j=0;j<11;j++) springs[j]->update(dt);
	
	for(int i=0;i<3;i++) points[i]->update(dt);

	for(int i=0;i<3;i++) circles[i]->update(dt);
	return false;
}

void CTank::acc(double ax,double ay) {
	for(int i=0;i<3;i++) {
		points[i]->accx+=ax;
		points[i]->accy+=ay;
	}
	for(int i=0;i<3;i++) {
		circles[i]->accx+=ax;
		circles[i]->accy+=ay;
	}
}

void CTank::mapCollide(IMap &map) {
	for(int i=0;i<3;i++) {
		const CPointMass& point = *points[i];
		double* d = map.penetration(point.posx,point.posy);

		double dx = d[0];
		double dy = d[1];
		double depth = sqrt(dx*dx+dy*dy);
		if(depth<0.0000001) {
			grounded[0] = false;
			grounded[1] = false;
			grounded[2] = false;
			continue;	
		}
		if(i==0)
			grounded[0] = true;
		else if(i==1)
			grounded[1] = true;
		else if(i==2)
			grounded[2] = true;
		double* spring = map.spring(point.posx,point.posy);
		double k = spring[0];
		double b = spring[1];

		double nx = -dx/depth;
		double ny = -dy/depth;
		double dp = nx*point.velx+ny*point.vely;
		double fx = nx*(k+fabs(engine))*depth;
		double fy = ny*(k+fabs(engine))*depth;
		double bx = b*nx*dp;
		double by = b*ny*dp;
		
		if(i==0) {
		mapForcex=(fx-bx);
		mapForcey=(fy-by);
		}
		

		double dp2 = ny*point.velx-nx*point.vely;
		double f2x = map.friction*ny*dp2-ny*engine/sqrt(1+depth);
		double f2y = -map.friction*nx*dp2+nx*engine/sqrt(1+depth);
		
		points[i]->accx+=(fx-bx-f2x)/point.mass;
		points[i]->accy+=(fy-by-f2y)/point.mass;
		delete d;
		delete spring;

	}
}

void CTank::draw(SDL_Surface* scr) {
	drawLineRel(scr,points[0]->posx,points[0]->posy,points[0]->velx,points[0]->vely,0,255,0);
	drawLineRel(scr,points[0]->posx,points[0]->posy,mapForcex,mapForcey,0,0,255);

	for(int j=0;j<11;j++) {
		springs[j]->draw(scr);
	}
	for(int i=0;i<3;i++) {
		points[i]->draw(scr);
	}
	for(int i=0;i<3;i++) {
		circles[i]->draw(scr);
	}
	double a = angle*(engine>0?1:-1)+(engine>0?3.14:0);
	for(int i=0;i<4;i++) drawLineRel(scr,circles[0]->posx,circles[0]->posy+i-6*scale,cos(a)*10*scale,sin(a)*10*scale,20,90,10);
}

void CTank::collide(IEnt &ent) {
	int count=0;
	CCircle** c=ent.getCircles(count);
	double* d = new double[2];
	for(int i=0;i<3;i++) {
		for(int j=0;j<count;j++) {
			d = CCircle::collideCircles(*circles[i],*c[j]);
			double dx=d[0];
			double dy=d[1];
			double depth = sqrt(dx*dx+dy*dy);
			
			if(depth>0) {
				static double k = 250*scale;
				static double b = 300*scale;

				double nx = -dx/depth;
				double ny = -dy/depth;
				double dp = nx*(circles[i]->velx-c[j]->velx)+ny*(circles[i]->vely-c[j]->vely);
				double fx = nx*k*depth;
				double fy = ny*k*depth;
				double bx = b*nx*dp;
				double by = b*ny*dp;
				points[i]->force(fx-bx,fy-by);
				
				c[j]->force(bx-fx,by-fy);

				}
			delete d;
			}
		}

}
