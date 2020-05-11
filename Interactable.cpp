#include "Interactable.hpp"

Interactable::Interactable() {
	name = new char[1000];
	desc = new char[1000];
	name = (char*)"default";
	desc = (char*)"default";
}

Interactable::Interactable(std::string nameIn, std::string descriptionIn) {
	name = new char[1000];
	desc = new char[1000];
	strcpy(name, nameIn.c_str());
	strcpy(desc, descriptionIn.c_str());
}

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

/*
Interactable::Interactable(): name{"default"}, shortDesc{"default"}, longDesc{"default"}, room{nullptr}, holdable{false} {}

Interactable::Interactable(std::string name_, std::string desc, Room* r, bool h):
	name{name_}, shortDesc{desc}, longDesc{desc}, room{r}, originalRoom{r}, holdable{h}

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

void Interactable::setOriginalRoom(Room* r){
	originalRoom = r;
}

void Interactable::setHoldable(bool h){
	holdable = h;
}

void Interactable::setGame(Game* g){
	game = g;
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

Room* Interactable::getOriginalRoom(){
	return originalRoom;
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
*/
