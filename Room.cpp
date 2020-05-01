#include "Room.hpp"


Room::Room() {
	roomNumber = -1;
	north = NULL;
	east = NULL;
	south = NULL;
	west = NULL;
	longDescription = new char[1000];
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

void Room::freeRoom(){
	delete longDescription;
}
