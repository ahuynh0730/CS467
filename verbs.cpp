#include "verbs.hpp"

#include <cmath>
#include <string>


void displayHelpList(WINDOW* win) {

	//clears and boxes window
	wclear(win);
	box(win, '|', '_');

	//list of available commands
	wmove(win, 1, 1);
	wprintw(win, "These are available commands during gameplay.");
	wmove(win, 2, 1);
	wprintw(win, "1. look : This repeats the long explanation of the room");
	wmove(win, 3, 1);
	wprintw(win, "2. look at : This gives an explanation or the object.");
	wmove(win, 4, 1);
	wprintw(win, "3. go : This allows you to travel to adjacent rooms.");
	wmove(win, 5, 1);
	wprintw(win, "4. take : This allows you to put an object in your inventory.");
	wmove(win, 6, 1);
	wprintw(win, "5. help : This will bring up the available commands during gameplay.");
	wmove(win, 7, 1);
	wprintw(win, "6. inventory : This will list the contents of your inventory.");

	wrefresh(win);
	move(0, 0);
	printw("Press any key to return to previous screen.");
	refresh();
	getch();
}

