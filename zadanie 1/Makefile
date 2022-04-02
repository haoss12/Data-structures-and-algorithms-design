TRGDIR=./
INC=./inc
OBJ=./obj
SRC=./src
FLAGS=-Wall -pedantic -iquote inc

__start__: ${TRGDIR}test
	${TRGDIR}test

${TRGDIR}test: ${OBJ} ${OBJ}/main.o ${OBJ}/PriorityQueue.o
	g++ -o ${TRGDIR}test ${OBJ}/main.o ${OBJ}/PriorityQueue.o 

${OBJ}:
	mkdir ${OBJ}

${OBJ}/main.o: ${SRC}/main.cpp ${INC}/PriorityQueue.hh
	g++ -c ${FLAGS} -o ${OBJ}/main.o ${SRC}/main.cpp

${OBJ}/PriorityQueue.o: ${SRC}/PriorityQueue.cpp ${INC}/PriorityQueue.hh
	g++ -c ${FLAGS} -o ${OBJ}/PriorityQueue.o ${SRC}/PriorityQueue.cpp

clear:
	rm -f ${TRGDIR}test.exe ${OBJ}/*

