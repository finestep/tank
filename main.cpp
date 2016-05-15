#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>

#include "util.h"


#include "ient.h"
#include "entman.h"

#include "ccontroller.h"

#include "cpointmass.h"
#include "cspring.h"

#include "ctank.h"
#include "imap.h"
#include "cmapslope.h"
#include "cmapheight.h"


int main(int argc, char **argv)
{
	printf("init\n");
	if( SDL_Init(SDL_INIT_VIDEO)<0 ) {
		printf("Init error: %s",SDL_GetError());
		exit(1);
	}
	atexit(SDL_Quit);
	SDL_Surface* _screen = SDL_SetVideoMode(640,480,32,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_ASYNCBLIT);
	EntMan* _entman = new EntMan();
	CController* _control = new CController();

	CTank* tank;

	for(int i=0;i<2;i++){
		tank = new CTank(480-i*320,360,_control->getState(i),.85);
		//tank->acc(6000,0);
		_entman->addEnt((IEnt*)tank);
	} 
	
	
//	IMap* map = new CMapSlope(0.4);
	IMap* map = new CMapHeight(640,1,1);
	for(double i=0;i<640;i++) map->set(i,480-60+10*sin(i*0.03));
//	for(int i=0;i<640;i++) ((CMapHeight*)map)->set(i,40);
//	CPointMass point1(1,300,20,-50,50);
//	CPointMass point2(1,340,20,0,0);
//	CSpring spring(point1,point2,4,1);

	
	
	double dt=1./60.;
	double* pene = new double[2];
	
	Uint32 frameEnd=SDL_GetTicks()-16;
	Uint32 frameStart;
	Uint32 frameTime;
	double accum=0;
	bool go=true;
	SDL_Event ev;
	while(go) {

		while( SDL_PollEvent(&ev) ) {
			if(ev.type==SDL_QUIT) go=false;
		}
		int mx, my;
		SDL_GetMouseState(&mx,&my);
		Uint8* keyState = SDL_GetKeyState(NULL);
		
		if(keyState[SDLK_ESCAPE]) go=false;
		_control->update(keyState);
		
		
		
		frameStart = SDL_GetTicks();
		frameTime = frameStart-frameEnd;
		//frameEnd = frameStart;
		

		
		
		accum+=frameTime;
		
		int stepCount=0;
		while(accum>0&&stepCount<40) {
			
			_entman->update(dt,map);
		
			accum-=dt*1000;
			stepCount++;
		}

		map->draw(_screen);
		_entman->draw(_screen);
	

		pene = map->penetration(mx,my);
		drawLineRel(_screen,mx,my,-pene[0],-pene[1]);
		
		SDL_Flip(_screen);
		frameEnd = frameStart;
		
		SDL_Delay(dt*1000-(frameEnd-frameStart));

		SDL_FillRect(_screen,NULL,SDL_MapRGB(_screen->format,70,40,130));
	}
	delete pene;
	delete map;
	
	delete _entman;
	delete _control;
	
	return 0;
}
