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