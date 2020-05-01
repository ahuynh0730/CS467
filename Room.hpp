#ifndef ROOM_hpp
#define ROOM_hpp

#include <iostream>
#include <string>
#include <string.h>

class Room{
private:
	int roomNumber;
	Room* up;
	Room* right;
	Room* down;
	Room* left;
	char* longDescription;

public:
	Room();
	void connectUp(Room*);
	void connectRight(Room*);
	void connectDown(Room*);
	void connectLeft(Room*);
	void setRoomNumber(int);
	void printRoomInfo();
	int getRoomNumber();
	void setLongDescription(std::string);
	char* getLongDescription();
	void freeRoom();

};

#endif
