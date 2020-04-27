#ifndef INTERACTABLE_hpp
#define INTERACTABLE_hpp

#include <string>
#include <vector>

class Interactable{
protected:
	std::string name;
	std::string description;
public:
	Interactable();
	void setName(std::string name_);
	void setDesc(std::string desc);
	std::string getName();
	std::string getDesc();
	virtual std::vector<std::string> listUserOptions();
	virtual bool callFunction(int n);
};

#endif
