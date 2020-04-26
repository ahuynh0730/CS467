#ifndef ROOM_hpp
#define ROOM_hpp


class Room{
private:
	Room* up;
	Room* right;
	Room* down;
	Room* left;

public:
	void connectUp(Room*);
	void connectRight(Room*);
	void connectDown(Room*);
	void connectLeft(Room*);

};

#endif
