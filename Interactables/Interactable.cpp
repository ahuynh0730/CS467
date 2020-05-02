#include "Interactable.hpp"

Interactable::Interactable(): name{"default"}, description{"default"}, room{nullptr}, holdable{false}, game{nullptr} {}

Interactable::Interactable(std::string name_, std::string desc, Room* r, Game* g, bool h):
	name{name_}, description{desc}, room{r}, holdable{h}, game{g} {}

void Interactable::setName(std::string name_){
	name = name_;
}

void Interactable::setDesc(std::string desc){
	description = desc;
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

std::string Interactable::getDesc(){
	return description;
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
