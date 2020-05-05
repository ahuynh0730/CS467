#include "Quiz.hpp"

Quiz::Quiz(): Interactable{}, successString{"default"}, failString{"default"}, isCorrect{false} {}

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
}
