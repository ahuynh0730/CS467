#include "Chest.hpp"

Chest::Chest(std::string nameIn, std::string descriptionIn, Interactable* keyIn) : Interactable(nameIn, descriptionIn), isLocked(true), key(keyIn) {
	type = 3;
}

bool Chest::getIsLocked(){
	return isLocked;
}

//returns item used to unlock it, or nullptr if not unlocked, or this if already unlocked
Interactable* Chest::unlock(std::vector<Interactable*> inventory){
	if(!isLocked){
		return this;
	}

	for(std::vector<Interactable*>::iterator it = inventory.begin(); it != inventory.end(); it++){
		if((*it) == key){
			isLocked = false;
			return key;
		}
	}

	return nullptr;
}


void Chest::addItem(Interactable* item){
	items.push_back(item);
}

std::vector<Interactable*> Chest::getItemsList() {
	return items;
}

void Chest::empty(){
	items.clear();
}

