#ifndef QUIZ_hpp
#define QUIZ_hpp

#include "Interactable.hpp"

class Quiz: public Interactable{
private:
	std::string successString;
	std::string failString;
	std::string correctAnswer;
	bool isCorrect;
public:
	Quiz();
	Quiz(std::string name_, std::string desc, Room* r, Game* g, bool h);
	void setSuccessString(std::string s);
	void setFailString(std::string s);
	void setIsCorrect(bool c);
	std::string getSuccessString();
	std::string getFailString();
	bool getIsCorrect();
	std::vector<std::string> listUserOptions();
	std::string callFunction(int n);
	std::string answer();
};

#endif