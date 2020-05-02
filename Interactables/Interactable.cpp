#include "Interactable.hpp"

Interactable::Interactable(): name{"default"}, description{"default"}, room{nullptr}, holdable{false}, game{nullptr} {}

Interactable::Interactable(std::string name_, std::string desc, Room* r, Game* g, bool h):
	name{name_}, description{desc}, room{r}, holdable{h}, game{g} {}

void Interactable::setName(std::string name_){
	name = name_;
}

void Interactable::setShortDesc(std::string desc){
	shortDesc = desc;
}

void Interactable::setLongDesc(std::string desc){
	longDesc = desc;
}

void Interactable::setRoom(Room* r){
	room = r;
}

void Interactable::setHoldable(bool h){
	holdable = h;
}

void Interactable::setGame(Game* g){
	game = g;
}

std::string Interactable::getName(){
	return name;
}

std::string Interactable::getShortDesc(){
	return shortDesc;
}

std::string Interactable::getLongDesc(){
	return longDesc;
}

Room* Interactable::getRoom(){
	return room;
}

bool Interactable::getHoldable(){
	return holdable;
}

Game* Interactable::getGame(){
	return game;
}

std::vector<std::string> Interactable::listUserOptions(){
	return std::vector<std::string>{"Describe"};
}

std::string Interactable::callFunction(int n){
	return longDesc;
}
