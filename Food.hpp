#ifndef FOOD_hpp
#define FOOD_hpp

#include <curses.h>
#include "common.hpp"
#include "Interactable.hpp"

class Food: public Interactable{
private:
	
public:
	Food();
	Food(std::string, std::string);
};

#endif