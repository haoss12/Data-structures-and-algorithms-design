TRGDIR=./
INC=./inc
OBJ=./obj
SRC=./src
FLAGS=-Wall -pedantic -iquote inc

__start__: ${TRGDIR}test
	${TRGDIR}test

${TRGDIR}test: ${OBJ} ${OBJ}/main.o
	g++ -o ${TRGDIR}test ${OBJ}/main.o  

${OBJ}:
	mkdir ${OBJ}

${OBJ}/main.o: ${SRC}/main.cpp ${INC}/movie.hh ${INC}/sorting_algs.hh
	g++ -c ${FLAGS} -o ${OBJ}/main.o ${SRC}/main.cpp


clear:
	rm -f ${TRGDIR}test.exe ${OBJ}/*

