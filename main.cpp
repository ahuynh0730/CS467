#include <curses.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "common.hpp"
#include "Game.hpp"

WINDOW* stdscr; 
WINDOW* win;
WINDOW* borderWindow;
const char* hitButton = "Please enter any button to continue.";
const int newWidth = 75;


int main() {	
	//include initializing screen, making sure screen is big enough, creating a new screen, and displaying the main menu
	const char* makeTaller = "Please make your console screen taller and try again.";
	const char* makeWider = "Please make your console screen wider and try again.";
	const char* makeWiderAndTaller = "Please make your console screen taller and wider. Try again afterwards.";
	const char* menuInstructions = "Please use the arrow keys to move up/down. Hit enter to select option.";
	char playerInput[100];
	int menuChoice;
	std::ifstream fload;
	
	

	//initializes screen, allocates memory for screen
	stdscr = initscr();
	
	
	
	//initializes and gets width and height of screen
	int height, width;
	getmaxyx(stdscr, height, width);

	//dimensions for new screen
	int newHeight, start_y, start_x;
	newHeight = 25;
	start_y = (height - newHeight) / 2;
	start_x = (width - newWidth) / 2;

	//will display message if screen needs to be bigger
	if (height < newHeight + 6 || width < newWidth + 4) {
		move(0, 0);
		if (height < newHeight + 6 && width < newWidth + 4) {
			printw(makeWiderAndTaller);
		}
		else if (height < newHeight + 6) {
			printw(makeTaller);
		}
		else if (width < newWidth + 4) {
			printw(makeWider);
		}
		move(1, 0);
		printw(hitButton);
		refresh();
		getch();
		endwin();
		return 0;
	}
	
	//will print instructions for menu
	move(0, 0);
	printw(menuInstructions);

	//creates new window from parameters
	//borderWindow will only be used for the border of the game
	borderWindow = newwin(newHeight + 2, newWidth + 2, start_y - 1, start_x - 1);
	box(borderWindow, '|', '_');
	win = newwin(newHeight, newWidth, start_y, start_x);
	refresh();
	wrefresh(borderWindow);
	

	//this allows arrow keys and enter button to be captured
	keypad(win, TRUE);

	//obtains menu choice from user and acts accordingly
	Game game1;
	menuChoice = game1.displayMainScreen();
	move(0, 0);
	clrtoeol();
	refresh();
	bool isLoading = false;
	switch (menuChoice) {
	
		//option for starting new game
		case 0:
			break;

		//option for loading game
		case 1:{
			isLoading = true;
			move(0, 0);
			clrtoeol();
			wclear(win);
			wmove(win, 0, 0);
			wprintw(win, "Enter your save file");
			wrefresh(win);
			move(0, 0);

			getstr(playerInput);
			std::string loadName = std::string("saveFiles/") + std::string(playerInput);
			struct stat st;
			while(true){
				if( isalpha(playerInput[0]) && stat(loadName.c_str(), &st) == 0 ){
					fload.open(loadName, std::fstream::in);
				}
				if( isalpha(playerInput[0]) && stat(loadName.c_str(), &st) == 0  && fload){
					break;
				}

				move(0, 0);
				clrtoeol();
				wclear(win);
				wmove(win, 0, 0);
				wprintw(win, "Save file does not exist, try again");
				wmove(win, 1, 0);
				wrefresh(win);

				getstr(playerInput);			
				loadName = "saveFiles/" + std::string(playerInput);
				wrefresh(win);
			}
			
			move(0, 0);
			clrtoeol();
			wclear(win);
			wmove(win, 0, 0);
			wprintw(win, "Loaded game");
			wmove(win, 24, 0);
			refresh();
			wprintw(win, hitButton);
			wrefresh(win);
			getch();
			wrefresh(win);
			break;
		}

		//option for quitting game
		case 2:
			delwin(win);
			delwin(borderWindow);
			endwin();
			return 0;
			break;
	}

	//intro
	game1.createRooms();
	if(!isLoading){
		game1.displayGameInfo();
		wmove(win, 24, 0);
		refresh();
		wprintw(win, hitButton);
		wrefresh(win);
		getch();
		wrefresh(win);
	}

	


	//write to temp file all commands user enters. Will use to save game
	std::string tempSaveFileName = "saveFiles/.temp" + std::to_string(getpid());
	std::ofstream fout;
	fout.open(tempSaveFileName, std::fstream::out | std::fstream::trunc);
	if(!fout){		
		move(0, 0);
		clrtoeol();
		wclear(win);
		wmove(win, 0, 0);
		wprintw(win, "Unable to open file for save");
		wmove(win, 24, 0);
		refresh();
		wprintw(win, hitButton);
		wrefresh(win);
		getch();
		wrefresh(win);

		//frees memory used by created subwindows
		delwin(win);
		delwin(borderWindow);
		
		//deallocates memory and ends ncurses
		endwin();
		game1.freeGame();

		exit(1);
	}


	//runs until game is over
	while (game1.getGameOverStatus() == false) {
		game1.addToRoomsVisited(game1.getCurrentRoom());
		game1.getCurrentRoom()->printDescription();
		move(0, 0);

		//get input
		if(isLoading){
			//gets command from save file, if eof then done loading
			if( !fload.getline(playerInput, 99, '\n') ){
				isLoading = false;
				fload.close();
				continue;
			}
		}
		else{
			//gets player command and will tell player if the command is invalid
			getstr(playerInput);
			for (unsigned int i = 0; i < strlen(playerInput); i++)
				playerInput[i] = tolower(playerInput[i]);
		}

		bool keep = true;

		//---------------------------------------------------
		//-----------input that doesn't needs saving---------
		//---------------------------------------------------
		if (strcmp("quitgame", playerInput) == 0) {
			game1.setGameOverStatus(true);
			break;
		}
		else if ( strncmp("savegame ", playerInput, 9) == 0 && isalpha(playerInput[9]) ) {
			game1.saveScreen();
			move(0, 0);
			clrtoeol();
			wclear(win);
			wmove(win, 0, 0);

			fout.close();
			std::string saveFileName = "saveFiles/" + std::string(&(playerInput[9]));
			fout.open(saveFileName, std::fstream::out | std::fstream::trunc | std::fstream::binary);
			std::ifstream fin;
			fin.open(tempSaveFileName, std::fstream::in | std::fstream::binary);
			if(!fout || !fin){
				wprintw(win, "Failed to save");
				wmove(win, 1, 0);
			}
			else{
				fout << fin.rdbuf();
				wprintw(win, "Saved successfully");
				wmove(win, 1, 0);
			}

			fin.close();
			fout.close();

			//go back to temp save file
			fout.open(tempSaveFileName, std::fstream::out | std::fstream::app);
			if(!fout){
				//frees memory used by created subwindows
				delwin(win);
				delwin(borderWindow);
				
				//deallocates memory and ends ncurses
				endwin();
				game1.freeGame();
				
				std::cerr << "Unable to open file for temp save." << std::endl;

				exit(1);
			}
			keep = false;
		}
		else if (strcmp("help", playerInput) == 0) {
			game1.displayHelpList();
			keep = false;
		}
		else if (strcmp("look", playerInput) == 0) {
			game1.saveScreen();
			wclear(win);
			game1.getCurrentRoom()->printLongDescription();
			keep = false;
		}
		else if (strncmp("look at ", playerInput, 8) == 0) {
			char* object = &(playerInput[8]);
			game1.lookAt(object);
			keep = false;
		}
		else if (strcmp("map", playerInput) == 0) {
			game1.displayMap();
			keep = false;
		}
		else if (strcmp("inventory", playerInput) == 0) {
			game1.displayInventory();
			keep = false;
		}
		else if (strncmp("question ", playerInput, 9) == 0) {
			char* object = &(playerInput[9]);
			game1.question(object);
			keep = false;
		}
		else if (strncmp("frisk ", playerInput, 6) == 0){
			char* suspect = &(playerInput[6]);
			game1.gameFrisk(suspect);
			keep = false;
		}
		//---------------------------------------------------
		//---------------------------------------------------
		//---------------------------------------------------


		//---------------------------------------------------
		//---------------input that needs saving-------------
		//---------------------------------------------------
		else if (strncmp("go ", playerInput, 2) == 0) {
			char* destination = &(playerInput[3]);
			game1.travelTo(destination);
		}
		else if (game1.getCurrentRoom()->getTravelVectorPosition((std::string) playerInput) != -1) {
			game1.travelTo(playerInput);
		}
		else if (strncmp("take ", playerInput, 5) == 0) {
			char* object = &(playerInput[5]);
			game1.gameTake(object);
		}
		else if (strncmp("accuse ", playerInput, 7) == 0) {
			char* object = &(playerInput[7]);
			game1.gameAccuse(object);
		}
		else if (strncmp("open ", playerInput, 5) == 0) {
			char* object = &(playerInput[5]);
			game1.open(object);
		}		
		else if (strncmp("unlock ", playerInput, 7) == 0) {
			char* object = &(playerInput[7]);
			game1.unlock(object);
		}		
		else if(strncmp("solve ", playerInput, 6) == 0){
			char* object = &(playerInput[6]);
			game1.solve(object);
		}
		else if(strncmp("drop ", playerInput, 5) == 0){
			char* object = &(playerInput[5]);
			game1.drop(object);
		}
		else if(strncmp("fasttravel room ", playerInput, 16) == 0){
			char* location = &(playerInput[16]);
			game1.fastTravel(location);
		}
		else if (strncmp("eat ", playerInput, 4) == 0){
			char* object = &(playerInput[4]);
			game1.gameEat(object);
		}
		//---------------------------------------------------
		//---------------------------------------------------
		//---------------------------------------------------


		else {
			game1.saveScreen();
			move(0, 0);
			clrtoeol();
			wclear(win);
			wmove(win, 0, 0);
			wprintw(win, "Invalid command. Please try again.");
			wmove(win, 1, 0);
			keep = false;
		}

		//save user's input
		if(keep)
			fout << playerInput << std::endl;
		
		if(!isLoading){
			//wait for player to press key to go forward
			wmove(win, 24, 0);
			refresh();
			wprintw(win, hitButton);
			wrefresh(win);
			getch();
			wrefresh(win);
			game1.previousScreen();
		}
	}

	//get rid of temp save file
	fout.close();
	if(std::remove(tempSaveFileName.c_str()) != 0){		
		move(0, 0);
		clrtoeol();
		wclear(win);
		wmove(win, 0, 0);
		wprintw(win, "Unable to delete temporary save file");
		wmove(win, 24, 0);
		refresh();
		wprintw(win, hitButton);
		wrefresh(win);
		getch();
	}

	
	//frees memory used by created subwindows
	delwin(win);
	delwin(borderWindow);
	


	//deallocates memory and ends ncurses
	endwin();
	game1.freeGame();
	

	return 0;
}
