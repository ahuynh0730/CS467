
CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g
#CXXFLAGS += -O3
LDFLAGS = -lboost_date_time

OBJS = main.o Game.o Room.o Suspect.o Interactable.o

SRCS = main.cpp Game.cpp Room.cpp Suspect.cpp Interactable.cpp
 
HEADERS = common.hpp Game.hpp Room.hpp Suspect.hpp Interactable.hpp

main: ${OBJS} ${HEADERS}
	${CXX} ${LDFLAGS} ${OBJS} -o main -lncurses

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

zip:
	zip -r teamRAN *.cpp *.hpp *.md makefile rooms/

clean:
	rm -f *.o main

