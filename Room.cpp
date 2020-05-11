#include "Room.hpp"


Room::Room() {
	roomNumber = -1;
	north = NULL;
	east = NULL;
	south = NULL;
	west = NULL;
	longDescription = new char[1000];
	shortDescription = new char[1000];
	visitedBefore = false;
}


void Room::connectUp(Room* roomAbove){
	north = roomAbove;
}

void Room::connectRight(Room* roomToRight){
	east = roomToRight;
}

void Room::connectDown(Room* roomBelow){
	south = roomBelow;
}

void Room::connectLeft(Room* roomToLeft){
	west = roomToLeft;
}

void Room::setRoomNumber(int number){
	roomNumber = number;
}


int Room::getRoomNumber(){
	return roomNumber;
}

void Room::setLongDescription(std::string input){
	strcpy(longDescription, input.c_str());
}

char* Room::getLongDescription(){
	return longDescription;
}

void Room::setShortDescription(std::string input){
	strcpy(shortDescription, input.c_str());
}

char * Room::getDescription()
{
	if (visitedBefore == false) {
		visitedBefore = true;
		return longDescription;
	}
	else {
		return shortDescription;
	}
}

std::vector<std::string> Room::getTravelCommandsVector()
{
	return travelCommands;
}

void Room::addTravelCommand(std::string input){
	travelCommands.push_back(input);
}

Room * Room::getNorthRoom(){
	return north;
}

Room * Room::getEastRoom() {
	return east;
}

Room* Room::getSouthRoom() {
	return south;
}

Room* Room::getWestRoom() {
	return west;
}

int Room::getTravelVectorPosition(std::string input){
	for (unsigned int i = 0; i < travelCommands.size(); i++) {
		if (travelCommands[i].find(input) != std::string::npos) {
			return i;
		}
	}
	return -1;
}

void Room::addInteractable(Interactable* i){
	items.push_back(i);
	/*std::set<Interactable*>::iterator it = items.find(i);
	if(it != items.end())
		return false;
	items.insert(i);
	return true;*/
}

bool Room::removeInteractable(Interactable* i){
	/*
	std::set<Interactable*>::iterator it = items.find(i);
	if(it == items.end())
		return false;
	items.erase(i);
	return true;	
	*/
	return true;
}

std::vector<Interactable*> Room::getItemsList() {
	return items;
}

int Room::getNumberItems() {
	return numberItems;
}

void Room::freeRoom(){
	delete longDescription;
	delete shortDescription;
}
