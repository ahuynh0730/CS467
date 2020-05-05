#ifndef GAME_hpp
#define GAME_hpp

#include <cmath>
#include <curses.h>
#include <dirent.h>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "common.hpp"
#include "Room.hpp"


class Game {
private:
	std::vector<Room> rooms;
	//std::map<std::string, Interactable*> interactables; //key is name of interactable
	Room* currentRoom;
	bool gameOver = false;
public:
	void displayGameInfo();
	void createInteractables();
	void freeInteractables();
	void createRooms();
	Room* getCurrentRoom();
	bool getGameOverStatus();
	void setGameOverStatus(bool status);
	void freeGame();
	void saveScreen();
	void previousScreen();
	int displayMainScreen();
	void loadGame();
	void lookAt();
	void travelTo(char*);
	void take();
	void displayHelpList();
	void displayInventory();
	void saveGame();

};

#endif