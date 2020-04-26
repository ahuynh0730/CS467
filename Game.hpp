#ifndef GAME_hpp
#define GAME_hpp

#include <curses.h>
#include <vector>
#include "common.hpp"
#include "Room.hpp"



class Game {
private:
	std::vector<Room> rooms;
	Room* currentRoom;
	bool gameOver = false;
public:
	void displayGameInfo();
	/*void startNewGame();
	void displayHelpList();
	void loadGame();*/
};

#endif