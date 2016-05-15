#include "ccontroller.h"

CController::CController()
{
	for(int i=0;i<4;i++) state[i]=CTRL_NONE;
}

CController::~CController()
{
}

void CController::update(Uint8* keys) {
	if(keys[SDLK_UP]) state[0]|=CTRL_UP;
	else state[0]&=~CTRL_UP;
	if(keys[SDLK_DOWN]) state[0]|=(Uint8)CTRL_DOWN;
	else state[0]&=~(Uint8)CTRL_DOWN;
	if(keys[SDLK_LEFT]) state[0]|=(Uint8)CTRL_LEFT;
	else state[0]&=~(Uint8)CTRL_LEFT;
	if(keys[SDLK_RIGHT]) state[0]|=(Uint8)CTRL_RIGHT;
	else state[0]&=~(Uint8)CTRL_RIGHT;
	if(keys[SDLK_RCTRL]) state[0]|=(Uint8)CTRL_FIRE;
	else state[0]&=~(Uint8)CTRL_FIRE;

	if(keys[SDLK_w]) state[1]|=CTRL_UP;
	else state[1]&=~CTRL_UP;
	if(keys[SDLK_s]) state[1]|=(Uint8)CTRL_DOWN;
	else state[1]&=~(Uint8)CTRL_DOWN;
	if(keys[SDLK_a]) state[1]|=(Uint8)CTRL_LEFT;
	else state[1]&=~(Uint8)CTRL_LEFT;
	if(keys[SDLK_d]) state[1]|=(Uint8)CTRL_RIGHT;
	else state[1]&=~(Uint8)CTRL_RIGHT;
	if(keys[SDLK_LCTRL]) state[1]|=(Uint8)CTRL_FIRE;
	else state[1]&=~(Uint8)CTRL_FIRE;
}
