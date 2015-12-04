CXX = g++
CXXFLAGS = -Wall -MMD

EXEC = bb7k
OBJECTS = academic.o coop.o gotodc.o osap.o tuition.o block.o dctime.o gym.o player.o board.o display.o main.o residences.o building.o goose.o needles.o slc.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS} 
.PHONY: clean
