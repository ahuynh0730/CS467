#include "Room.hpp"


Room::Room() {
	roomNumber = -1;
	up = NULL;
	right = NULL;
	down = NULL;
	left = NULL;
}


void Room::connectUp(Room* roomAbove){
	up = roomAbove;
}

void Room::connectRight(Room* roomToRight){
	right = roomToRight;
}

void Room::connectDown(Room* roomBelow){
	down = roomBelow;
}

void Room::connectLeft(Room* roomToLeft){
	left = roomToLeft;
}

void Room::setRoomNumber(int number){
	roomNumber = number;
}

void Room::printRoomInfo(){
	std::cout << "Room " << roomNumber << std::endl;
	if (up != NULL) {
		std::cout << "room to the top number: " << up->getRoomNumber() << std::endl;
	}
	
	if (right != NULL) {
		std::cout << "room to the right number: " << right->getRoomNumber() << std::endl;
	}
	if (down != NULL) {
		std::cout << "room to the bottom number: " << down->getRoomNumber() << std::endl;
	}
	if (left != NULL) {
		std::cout << "room to the left number: " << left->getRoomNumber() << std::endl;
	}
	std::cout << std::endl;


}

int Room::getRoomNumber()
{
	return roomNumber;
}
