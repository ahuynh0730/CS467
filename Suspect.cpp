#include "Suspect.hpp"

Suspect::Suspect(): isMurderer(false) {
	type = 1;
}

Suspect::Suspect(std::string nameIn, std::string descriptionIn, bool isGuilty, std::string answerIn) : Interactable(nameIn, descriptionIn), isMurderer(isGuilty) {
	type = 1;
	answer = new char[1000];
	strcpy(answer, answerIn.c_str());
}

Suspect::~Suspect(){
	delete[] answer;
}

void Suspect::question(){
	wclear(win);
	wmove(win, 0, 0);
	wprintw(win, answer);
	wmove(win, 1, 0);
}

bool Suspect::accuse() {
	if (isMurderer) {
		wclear(win);
		wmove(win, 0, 0);
		wprintw(win, "Congratulations! You accused the correct person!");
	}
	else {
		wclear(win);
		wmove(win, 0, 0);
		wprintw(win, "Sorry! They were not the murderer!");
	}
	return true;
}

void Suspect::frisk(){
	if (isMurderer){
		wmove(win, 0, 0);
		wprintw(win, "After frisking the suspect, you found a knife covered in blood.");
	} else {
		wmove(win, 0, 0);
		wprintw(win, "You did not find anything.");
	}
}

