#ifndef ENTMAN_H
#define ENTMAN_H

#include <vector>
#include "ient.h"
#include "imap.h"

class IEnt;

class EntMan
{
	std::vector<IEnt*> ents;
	std::vector<IEnt*> toAdd;
public:
	EntMan();
	~EntMan();

	inline void addEnt(IEnt* ent) {
		toAdd.push_back(ent);
	}
	
	void update(double dt,IMap* map);
	
	void draw(SDL_Surface* scr);
};


#endif // ENTMAN_H
