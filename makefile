
CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g
#CXXFLAGS += -O3
LDFLAGS = -lboost_date_time

OBJS = main.o Game.o Room.o Interactable.o Suspect.o Quiz.o Chest.o Block.o

SRCS = main.cpp Game.cpp Room.cpp Interactable.cpp Suspect.cpp Quiz.cpp Chest.cpp Block.cpp
 
HEADERS = common.hpp Game.hpp Room.hpp Interactable.hpp Suspect.hpp Quiz.hpp Chest.hpp Block.hpp

main: ${OBJS} ${HEADERS}
	${CXX} ${LDFLAGS} ${OBJS} -o main -lncurses

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

zip:
	zip -r teamRAN *.cpp *.hpp *.md makefile rooms/

clean:
	rm -f *.o main

