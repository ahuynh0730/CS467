#include "Interactable.hpp"

Interactable::Interactable(): type(0) {
	name = new char[1000];
	desc = new char[1000];
	name = (char*)"default";
	desc = (char*)"default";
}

Interactable::Interactable(std::string nameIn, std::string descriptionIn): type(0) {
	name = new char[1000];
	desc = new char[1000];
	strcpy(name, nameIn.c_str());
	strcpy(desc, descriptionIn.c_str());
}

Interactable::~Interactable() {}


void Interactable::setName(std::string name_) {
	strcpy(name, name_.c_str());
}

char* Interactable::getName() {
	return name;
}

void Interactable::freeInteractable() {
	delete(name);
	delete(desc);
}

char* Interactable::getDescription() {
	return desc;
}

int Interactable::getType(){
	return type;
}

//------------------------------------------------
//-------------virtual functions------------------
//------------------------------------------------
//-------------Suspect-----------------------------
bool Interactable::accuse(){
	wmove(win, 0, 0);
	wprintw(win, "That object cannot be accused.");
	return false;
}

void Interactable::question(){
	wmove(win, 0, 0);
	wprintw(win, "That object cannot be questioned.");
	wmove(win, 1, 0);
}

void Interactable::frisk(){
	wmove(win, 0, 0);
	wprintw(win, "That object cannot be frisked.");
}

//----------------Quiz---------------------------
Interactable* Interactable::solve(char* ans){
	wmove(win, 0, 0);
	wprintw(win, "This is not a solvable object.");
	return nullptr;
}

//-------------Chest------------------------------
Interactable* Interactable::unlock(std::vector<Interactable*>){
	wmove(win, 0, 0);
	wprintw(win, "That object cannot be unlocked.");
	return nullptr;
}

bool Interactable::getIsLocked(){
	return false;
}

void Interactable::addItem(Interactable* item){
	wmove(win, 0, 0);
	wprintw(win, "That object cannot contain items.");
}

//--------Keys, etc -----------------------
bool Interactable::take(){
	if (type == 0 || type == 7) {
		return true;
	}
	else {
		return false;
	}
}

std::vector<Interactable*> Interactable::getItemsList(){
	return std::vector<Interactable*>();
}

void Interactable::empty(){}
//------------------------------------------------
//------------------------------------------------
//------------------------------------------------



