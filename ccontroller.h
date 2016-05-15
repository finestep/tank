#ifndef CCONTROLLER_H
#define CCONTROLLER_H

#include <SDL/SDL.h>
#include <assert.h>

typedef enum ECtrl {
	CTRL_NONE=0,
	CTRL_UP=1,
	CTRL_DOWN=2,
	CTRL_LEFT=4,
	CTRL_RIGHT=8,
	CTRL_FIRE=16
} ECtrl;

class CController
{
	Uint8 state[4];
public:
	CController();
	~CController();
	void update(Uint8* keys);
	inline Uint8* getState(Uint8 id) {
		assert(id>=0&&id<4);
		return &state[id];
	}
};

#endif // CCONTROLLER_H
