SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
MAN_DIR = man

CC = gcc
CFLAGS = -g -I ${SRC_DIR}

OBJS = ${OBJ_DIR}/crab.o ${OBJ_DIR}/crab_action.o ${OBJ_DIR}/term_colour.o ${OBJ_DIR}/alias.o ${OBJ_DIR}/history.o
BINS = ${BIN_DIR}/crab
MANPAGES = ${MAN_SIR}/cd.1.gz  ${MAN_DIR}/colour.1.gz  ${MAN_DIR}/history.1.gz  ${MAN_DIR}/listAll.1.gz

${BIN_DIR}/crab: ${SRC_DIR}/crab_main.c ${OBJS}
	${CC} ${CFLAGS} ${SRC_DIR}/crab_main.c ${OBJS} -o ${BIN_DIR}/crab -lreadline

${OBJ_DIR}/crab.o: ${SRC_DIR}/crab.h ${SRC_DIR}/crab.c
	${CC} ${CFLAGS} ${SRC_DIR}/crab.c -c -o ${OBJ_DIR}/crab.o

${OBJ_DIR}/crab_action.o: ${SRC_DIR}/crab_action.h ${SRC_DIR}/crab_action.c
	${CC} ${CFLAGS} ${SRC_DIR}/crab_action.c -c -o ${OBJ_DIR}/crab_action.o

${OBJ_DIR}/term_colour.o: ${SRC_DIR}/term_colour.h ${SRC_DIR}/term_colour.c
	${CC} ${CFLAGS} ${SRC_DIR}/term_colour.c -c -o ${OBJ_DIR}/term_colour.o


${OBJ_DIR}/history.o: ${SRC_DIR}/history.h ${SRC_DIR}/history.c
	${CC} ${CFLAGS} ${SRC_DIR}/history.c -c -o ${OBJ_DIR}/history.o

${OBJ_DIR}/alias.o: ${SRC_DIR}/alias.h ${SRC_DIR}/alias.c
	${CC} ${CFLAGS} ${SRC_DIR}/alias.c -c -o ${OBJ_DIR}/alias.o

install: ${BIN_DIR}/crab
	cp ${BIN_DIR}/crab /bin/
	cp ${MAN_DIR}/*.gz /usr/share/man/man1/
	mandb

uninstall:
	rm /bin/crab
	cd ${MAN_DIR}; \
	for i in *; do \
		rm -f /usr/share/man/man1/$$i; \
	done
	mandb

clean:
	rm -f ${OBJS} ${BINS}
