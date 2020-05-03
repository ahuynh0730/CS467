#ifndef ROOM_hpp
#define ROOM_hpp

#include <iostream>
#include <string>
#include <string.h>
#include <vector>

class Room{
private:
	int roomNumber;
	Room* north;
	Room* east;
	Room* south;
	Room* west;
	char* longDescription;
	char* shortDescription;
	std::vector<std::string> travelCommands;
	bool visitedBefore;

public:
	Room();
	void connectUp(Room*);
	void connectRight(Room*);
	void connectDown(Room*);
	void connectLeft(Room*);
	void setRoomNumber(int);
	int getRoomNumber();
	void setLongDescription(std::string);
	char* getLongDescription();
	void setShortDescription(std::string);
	char* getDescription();
	std::vector<std::string> getTravelCommandsVector();
	void addTravelCommand(std::string);
	Room* getNorthRoom();
	Room* getEastRoom();
	Room* getSouthRoom();
	Room* getWestRoom();
	int getTravelVectorPosition(std::string);
	void freeRoom();

};

#endif
