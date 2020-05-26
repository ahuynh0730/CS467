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


void Room::setShortDescription(std::string input){
	strcpy(shortDescription, input.c_str());
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
		if (input.length() != travelCommands[i].length() - 1){
			continue;
		}
		for (unsigned int j = 0; j < travelCommands[i].length(); j++){
			if (input[j] != travelCommands[i][j]){
				break;
			}
			if (j == travelCommands[i].length() - 2){
				return i;
			}
		}
	}
	return -1;
}

int Room::getItemsListPosition(std::string input) {
	
	for (unsigned int i = 0; i < items.size(); i++) {
		std::string name = items[i]->getName();
		if (input.length() != name.length() - 1){
			continue;
		}
		for (unsigned int j = 0; j < name.length(); j++){
			if (input[j] != name[j]){
				break;
			}
			if (j == name.length() - 2){
				return i;
			}
		}
	}
	return -1;
}

void Room::addInteractable(Interactable* i){
	items.push_back(i);
}

bool Room::removeInteractable(Interactable* i){
	for(std::vector<Interactable*>::iterator it = items.begin(); it != items.end(); it++){
		if(i == (*it)){
			items.erase(it);
			return true;
		}
	}
	return false;
	/*
	std::set<Interactable*>::iterator it = items.find(i);
	if(it == items.end())
		return false;
	items.erase(i);
	return true;	
	*/
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

void Room::printLongDescription(){
	int row = 0;
	move(0, 0);
	clrtoeol();
	wclear(win);
	wmove(win, row, newWidth / 2 - 3);
	wprintw(win, "Room %d", roomNumber);
	row++;
	wmove(win, row, 0);
	wprintw(win, longDescription);
	for (unsigned int i = 0; i < strlen(longDescription); i++) {
		if (longDescription[i] == '\n') {
			row++;
		}
	}
	row++;
	for (unsigned int i = 0; i < items.size(); i++) {
		wmove(win, row, 0);
		wprintw(win, "\t%s", items[i]->getName());
		row++;
	}
	wrefresh(win);
}

void Room::printDescription(){
	if (visitedBefore == false) {
		visitedBefore = true;
		printLongDescription();
	}
	else {
		int row = 0;
		move(0, 0);
		clrtoeol();
		wclear(win);
		wmove(win, row, newWidth / 2 - 3);
		wprintw(win, "Room %d", roomNumber);
		row++;
		wmove(win, row, 0);
		wprintw(win, shortDescription);
		wrefresh(win);
	}
}
