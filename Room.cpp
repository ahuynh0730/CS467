#include "Room.hpp"


Room::Room() {
	roomNumber = -1;
	north = NULL;
	east = NULL;
	south = NULL;
	west = NULL;
	baseDescription = new char[1000];
	longDescription = new char[2000];
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

int Room::getRoomNumber() {
	return roomNumber;
}

void Room::setRoomNumber(int number){
	roomNumber = number;
}

void Room::setBaseDescription(std::string input) {
	strcpy(baseDescription, input.c_str());
}

void Room::setLongDescription(){
	memset(longDescription, 0, 2000);
	strcpy(longDescription, baseDescription);
	for (unsigned int i = 0; i < items.size(); i++) {
		strcat(longDescription, "\n\t");
		strcat(longDescription, items[i]->getName());
	}
}

char* Room::getLongDescription(){
	setLongDescription();
	return longDescription;
}

void Room::setShortDescription(std::string input){
	strcpy(shortDescription, input.c_str());
}

char * Room::getDescription()
{
	if (visitedBefore == false) {
		visitedBefore = true;
		setLongDescription();
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

int Room::getItemsListPosition(std::string input) {
	for (unsigned int i = 0; i < items.size(); i++) {
		std::string name = items[i]->getName();
		if (name.find(input) != std::string::npos) {
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
	delete baseDescription;
	delete longDescription;
	delete shortDescription;
}
