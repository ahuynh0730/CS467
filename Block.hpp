#ifndef BLOCK_hpp
#define BLOCK_hpp

#include "Interactable.hpp"

class Block: public Interactable{
private:
	std::string blockedString;
	bool isBlocked;
public:
	Block();
	Block(std::string, std::string, std::string);
};

#endif
