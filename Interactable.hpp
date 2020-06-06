#ifndef INTERACTABLE_hpp
#define INTERACTABLE_hpp

#include <curses.h>
#include <string>
#include <string.h>
#include <vector>
#include "common.hpp"
//#include "Room.hpp"
//#include "Game.hpp"

class Interactable{
protected:
	
	char* name;
	char* desc;
	int type; //refer to room template for type number

public:

	Interactable();
	Interactable(std::string, std::string);
	virtual ~Interactable();
	void setName(std::string);
	char* getName();
	void freeInteractable();
	char* getDescription();
	int getType();
	virtual bool accuse();
	virtual void question();
	virtual Interactable* unlock(std::vector<Interactable*>);
	virtual bool getIsLocked();
	virtual void empty();
	virtual void addItem(Interactable*);
	virtual Interactable* solve(char*); 
	bool take();
	virtual void frisk();
	virtual std::vector<Interactable*> getItemsList();

};

#endif
