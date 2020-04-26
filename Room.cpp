#include "Room.hpp"
#include <iostream>

void Room::connectUp(Room * roomAbove){
	up = roomAbove;
}

void Room::connectRight(Room * roomToRight){
	right = roomToRight;
}

void Room::connectDown(Room * roomBelow){
	down = roomBelow;
}

void Room::connectLeft(Room * roomToLeft){
	left = roomToLeft;
}
