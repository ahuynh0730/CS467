#ifndef CHEST_hpp
#define CHEST_hpp

#include "Interactable.hpp"

class Chest: public Interactable{
private:
	bool isLocked;
	std::vector<Interactable*> items;
	Interactable* key;
public:
	Chest(std::string, std::string, Interactable*);
	Interactable* unlock(std::vector<Interactable*>);
	void open();
	bool getIsLocked();
	void addItem(Interactable*);
	std::vector<Interactable*> getItemsList();
	void empty();
};

#endif
