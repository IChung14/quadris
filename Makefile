CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = quadris
OBJECTS = main.o subject.o level.o grid.o game.o cell.o block.o control.o window.o graphicdisplay.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
