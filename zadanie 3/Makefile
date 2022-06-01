TRGDIR=./
INC=./inc
OBJ=./obj
SRC=./src
FLAGS=-Wall -pedantic -iquote inc

__start__: ${TRGDIR}tictactoe
	${TRGDIR}tictactoe

${TRGDIR}tictactoe: ${OBJ} ${OBJ}/main.o
	g++ -o ${TRGDIR}tictactoe ${OBJ}/main.o  

${OBJ}:
	mkdir ${OBJ}

${OBJ}/main.o: ${SRC}/main.cpp
	g++ -c ${FLAGS} -o ${OBJ}/main.o ${SRC}/main.cpp


clear:
	rm -f ${TRGDIR}tictactoe.exe ${OBJ}/*

