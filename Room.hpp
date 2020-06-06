#ifndef ROOM_hpp
#define ROOM_hpp

#include <curses.h>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <set>
#include "common.hpp"
#include "Interactable.hpp"


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
	bool naturallyDark;
	std::vector<Interactable*> items;

	int numberItems;

public:
	Room();
	void connectUp(Room*);
	void connectRight(Room*);
	void connectDown(Room*);
	void connectLeft(Room*);
	void setRoomNumber(int);
	int getRoomNumber();
	void setLongDescription(std::string);
	void setShortDescription(std::string);
	std::vector<std::string> getTravelCommandsVector();
	void addTravelCommand(std::string);
	Room* getNorthRoom();
	Room* getEastRoom();
	Room* getSouthRoom();
	Room* getWestRoom();
	int getTravelVectorPosition(std::string);
	int getItemsListPosition(std::string);
	Interactable* getItemAtPosition(unsigned int);
	void addInteractable(Interactable*);
	bool removeInteractable(Interactable*);
	std::vector<Interactable*> getItemsList();
	int getNumberItems();
	void freeRoom();
	void setDarkness(bool);
	bool containsCandle();
	

	void printLongDescription();
	void printDescription();

};

#endif
