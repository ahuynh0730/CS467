#include "Game.hpp"

void Game::displayGameInfo() {

	//clears and boxes window 
	wclear(win);
	box(win, '|', '_');

	//moves cursor and displays starting game message
	wmove(win, 1, 1);
	wprintw(win, "Welcome to Murder Mystery2.");
	wmove(win, 2, 1);
	wprintw(win, "Somebody has been murdered and it is up to you to find the killer and");
	wmove(win, 3, 1);
	wprintw(win, "\tbring them to justice.");
	wmove(win, 4, 1);
	wprintw(win, "There are a number of rooms you must explore. The first room is where");
	wmove(win, 5, 1);
	wprintw(win, "\tyou will start. All of the suspects have been detained in this");
	wmove(win, 6, 1);
	wprintw(win, "\troom. The other rooms will contain clues or puzzles that");
	wmove(win, 7, 1);
	wprintw(win, "\twill lead you to clues.");
	wmove(win, 8, 1);
	wprintw(win, "You win the game by guessing the correct murderer. You may guess who");
	wmove(win, 9, 1);
	wprintw(win, "\tthe murderer is at any point, but if you are wrong, the game");
	wmove(win, 10, 1);
	wprintw(win, "\tends and you lose.");
	wmove(win, 11, 1);
	wprintw(win, "At any point in the game, you may type help to see a list of possible");
	wmove(win, 12, 1);
	wprintw(win, "\t commands.");
	wmove(win, 13, 1);
	wprintw(win, hitButton);
	move(0, 0);
	wrefresh(win);
	getch();

}

void Game::createRooms() {
	std::ifstream inFile;
	std::string inputLine;
	std::string pathName;
	int roomNumber, up, right, down, left;

	for (int i = 0; i < 15; i++) {
		rooms.push_back(Room());
	}
	

	
	for (int i = 1; i < 16; i++) {
		pathName = "rooms/room" + std::to_string(i) + ".txt";
		inFile.open(pathName);
		inFile >> roomNumber >> up >> right >> down >> left;
		
		//decrementing numbers to account for zero indexing
		//numbers will be -1 if 0 was read in(or null)
		roomNumber--;
		up--;
		right--;
		down--;
		left--;


		rooms[roomNumber].setRoomNumber(roomNumber + 1);
		std::cout << roomNumber << ", " << up << ", " << right << ", " << down << ", " << left << std::endl;
		
		//will assign pointer to correct room unless it is < 0
		if (up > -1) {
			rooms[roomNumber].connectUp(&(rooms[up]));
		}
		if (right > -1) {
			rooms[roomNumber].connectRight(&(rooms[right]));
		}
		if (down > -1) {
			rooms[roomNumber].connectDown(&(rooms[down]));
		}
		if (left > -1) {
			rooms[roomNumber].connectLeft(&(rooms[left]));
		}

		inFile.close();
	}

	for (unsigned int i = 0; i < rooms.size(); i++) {
		rooms[i].printRoomInfo();
	}
	



}