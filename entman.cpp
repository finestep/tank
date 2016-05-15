#include "entman.h"

typedef std::vector<IEnt*>::iterator entIter;

EntMan::EntMan()
{
	ents=std::vector<IEnt*>();
	toAdd=std::vector<IEnt*>();
}

EntMan::~EntMan()
{
	entIter i=ents.begin();
 	while(i!=ents.end()) {
		delete *i;
		i=ents.erase(i);
	}
	i=toAdd.begin();
 	while(i!=toAdd.end()) {
		delete *i;
		i=toAdd.erase(i);
	}
}

void EntMan::update(double dt,IMap* map) {

	entIter i=toAdd.begin();
 	while(i!=toAdd.end()) {
		ents.push_back(*i);
		i=toAdd.erase(i);
	}	

	i=ents.begin();
 	while(i!=ents.end()) {
		(*i)->acc(0,map->globalAcc);
		(*i)->mapCollide(*map);
		for(entIter j=i+1;j!=ents.end();j++) {
			(*j)->collide(**i);
		}	
		if((*i)->update(dt,this)) {
			delete *i;
			i=ents.erase(i);
		} else i++;
		
	}


}


void EntMan::draw(SDL_Surface* scr) {
 	for(entIter i=ents.begin();i!=ents.end();i++) (*i)->draw(scr);
}

