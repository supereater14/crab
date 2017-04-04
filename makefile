SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
MAN_DIR = man

CC = gcc
CFLAGS = -g -I ${SRC_DIR}

OBJS = ${OBJ_DIR}/crab.o ${OBJ_DIR}/crab_action.o ${OBJ_DIR}/term_colour.o
BINS = ${BIN_DIR}/crab

${BIN_DIR}/crab: ${SRC_DIR}/crab_main.c ${OBJ_DIR}/crab.o ${OBJ_DIR}/crab_action.o ${OBJ_DIR}/term_colour.o
	${CC} ${CFLAGS} -lreadline ${SRC_DIR}/crab_main.c ${OBJ_DIR}/term_colour.o ${OBJ_DIR}/crab.o ${OBJ_DIR}/crab_action.o -o ${BIN_DIR}/crab
    cp ${MAN_DIR}/ /usr/share/man/man1

${OBJ_DIR}/crab.o: ${SRC_DIR}/crab.h ${SRC_DIR}/crab.c
	${CC} ${CFLAGS} ${SRC_DIR}/crab.c -c -o ${OBJ_DIR}/crab.o

${OBJ_DIR}/crab_action.o: ${SRC_DIR}/crab_action.h ${SRC_DIR}/crab_action.c
	${CC} ${CFLAGS} ${SRC_DIR}/crab_action.c -c -o ${OBJ_DIR}/crab_action.o

${OBJ_DIR}/term_colour.o: ${SRC_DIR}/term_colour.h ${SRC_DIR}/term_colour.c
	${CC} ${CFLAGS} ${SRC_DIR}/term_colour.c -c -o ${OBJ_DIR}/term_colour.o

clean:
	rm -f ${OBJS} ${BINS}

