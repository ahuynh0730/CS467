#include "Quiz.hpp"

Quiz::Quiz(): Interactable{}, successString{"default"}, failString{"default"}, items{std::vector<Interactable*>{}}, isCorrect{false} {}

Quiz::Quiz(std::string name_, std::string desc, Room* r, Game* g, bool h, bool c):
	Interactable{std::string name_, std::string desc, Room* r, Game* g, h}, successString{"default"}, failString{"default"}, items{std::vector<Interactable*>{}}, isCorrect{c}  {}

bool Quiz::addItem(Interactable* i){
	std::set<Interactable*>::iterator it = items.find(i);
	if(it != items.end())
		return false;
	items.insert(i);
	return true;
}

bool Quiz::removeItem(Interactable*){
	std::set<Interactable*>::iterator it = items.find(i);
	if(it == items.end())
		return false;
	items.erase(i);
	return true;
}

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
	return std::vector<std::string>{"Answer"};
}

std::string Quiz::callFunction(int n){
	return answer();
}

std::string answer(){
	
}
