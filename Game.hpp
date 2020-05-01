#ifndef GAME_hpp
#define GAME_hpp

#include <cmath>
#include <curses.h>
#include <dirent.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include "common.hpp"
#include "Room.hpp"



class Game {
private:
	std::vector<Room> rooms;
	Room* currentRoom;
	bool gameOver = false;
public:
	void displayGameInfo();
	void createRooms();
	Room* getCurrentRoom();
	bool getGameOverStatus();
	void freeGame();
	void displayHelpList();
	void saveScreen();
	void previousScreen();
	int displayMainScreen();
	void loadGame();
};

#endif