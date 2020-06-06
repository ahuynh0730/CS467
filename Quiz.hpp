#ifndef QUIZ_hpp
#define QUIZ_hpp

#include <curses.h>
#include "common.hpp"
#include "Interactable.hpp"

class Quiz: public Interactable{
private:
	std::string successString; 
	std::string failString;
	std::string correctAnswer;
	bool isCorrect;
	Interactable* reward;
public:
	Quiz(std::string, std::string, std::string, Interactable*);
	virtual Interactable* solve(char*); 
	
};

#endif
