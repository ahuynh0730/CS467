#ifndef CHEST_hpp
#define CHEST_hpp

#include "Interactable.hpp"

class Chest: public Interactable{
private:
	bool isLocked;
	std::vector<Interactable*> items;
public:
	Chest(std::string, std::string);
	bool unlock();
	void addItem(Interactable*);
	std::vector<Interactable*> getItemsList();
};

#endif
