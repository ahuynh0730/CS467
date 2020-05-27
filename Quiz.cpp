#include "Quiz.hpp"

Quiz::Quiz() {

}

Quiz::Quiz(std::string nameIn, std::string descriptionIn, std::string answerIn) : Interactable(nameIn, descriptionIn) {
	correctAnswer = answerIn;
}

void Quiz::solve(){
	char playerInputCharArray[100];
	wmove(win, 0, 0);
	wprintw(win, desc);
	wrefresh(win);
	move(0, 0);
	getstr(playerInputCharArray);
	
	//changes first letter to upper case and rest to lowercase
	playerInputCharArray[0] = toupper(playerInputCharArray[0]);
	for (int i = 1; i < 100; i++){
		playerInputCharArray[i] = tolower(playerInputCharArray[i]);
	}
	std::string playerInput = (std::string) playerInputCharArray;
	
	//input is incorrect if not the correct length
	if(playerInput.length() == correctAnswer.length() - 1){
		
		for (unsigned int i = 0; i < correctAnswer.length() - 1; i++){
			//if incorrect will break out of loop
			if (playerInput[i] != correctAnswer[i]){
				break;
			}
			
			//if correct, will print congratulations and return 
			if (i == correctAnswer.length() - 2){
				wclear(win);
				wmove(win, 0, 0);
				wprintw(win, "Congratulations, that is the correct answer.");
				wmove(win, 1, 0);
				wprintw(win, hitButton);
				wrefresh(win);
				return;
			}
		}
	}

	//wrong answer output
	wclear(win);
	wmove(win, 0, 0);
	wprintw(win, "Sorry, that is not the correct answer.");
	wmove(win, 1, 0);
	wprintw(win, hitButton);
	wrefresh(win);

}

/*Quiz::Quiz(): Interactable{}, successString{"default"}, failString{"default"}, isCorrect{false} {}

Quiz::Quiz(std::string name_, std::string desc, Room* r, Game* g, bool h, bool c):
	Interactable{name_, desc, r, g, h}, successString{"default"}, failString{"default"}, isCorrect{c}  {}

void Quiz::setSuccessString(std::string s){
	successString = s;
}

void Quiz::setFailString(std::string s){
	failString = s;
}

void Quiz::setCorrectAnswer(std::string s){
	correctAnswer = s;
}

void Quiz::setIsCorrect(bool c){
	isCorrect = c;
}

std::string Quiz::getSuccessString(){
	return successString;
}

std::string Quiz::getFailString(){
	return failString;
}

std::string Quiz::getCorrectAnswer(){
	return correctAnswer;
}

bool Quiz::getIsCorrect(){
	return isCorrect;
}

std::vector<std::string> Quiz::listUserOptions(){
	return std::vector<std::string>{"Describe", "Answer"};
}

std::string Quiz::callFunction(int n){
	switch(n){
		case 0:
			return longDesc;
			break;
		case 1:
			return answer();
			break;
		default:
			return "You cannot do that.";
	}
}

std::string answer(){
	std::string ans;
	getstr(ans);
	for (int i = 0; i < std::strlen(ans); i++) {
		ans[i] = std::tolower(ans[i]);

	if(std::strcmp(ans, correctAnswer) == 0){
		isCorrect = true;
		return successString;
	}
	else{
		isCorrect = false;
		return failString;
	}
}*/
