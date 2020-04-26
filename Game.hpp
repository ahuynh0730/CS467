#ifndef GAME_hpp
#define GAME_hpp

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
	/*void startNewGame();
	void displayHelpList();
	void loadGame();*/
};

#endif