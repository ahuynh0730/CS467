#ifndef ROOM_hpp
#define ROOM_hpp

#include <iostream>

class Room{
private:
	int roomNumber;
	Room* up;
	Room* right;
	Room* down;
	Room* left;

public:
	Room();
	void connectUp(Room*);
	void connectRight(Room*);
	void connectDown(Room*);
	void connectLeft(Room*);
	void setRoomNumber(int);
	void printRoomInfo();
	int getRoomNumber();

};

#endif
