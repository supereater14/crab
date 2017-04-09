SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

CC = gcc
CFLAGS = -g -I ${SRC_DIR}

OBJS = ${OBJ_DIR}/crab.o ${OBJ_DIR}/term_colour.o ${OBJ_DIR}/alias.o ${OBJ_DIR}/crab_action.o $(OBJDIR)/view_main.o
BINS = ${BIN_DIR}/crab

${BIN_DIR}/crab: ${SRC_DIR}/crab_main.c ${OBJS}
	${CC} ${CFLAGS} ${SRC_DIR}/crab_main.c ${OBJS} -o ${BIN_DIR}/crab -lreadline

${OBJ_DIR}/crab.o: ${SRC_DIR}/crab.h ${SRC_DIR}/crab.c
	${CC} ${CFLAGS} ${SRC_DIR}/crab.c -c -o ${OBJ_DIR}/crab.o

${OBJ_DIR}/crab_action.o: ${SRC_DIR}/crab_action.h ${SRC_DIR}/crab_action.c
	${CC} ${CFLAGS} ${SRC_DIR}/crab_action.c -c -o ${OBJ_DIR}/crab_action.o

${OBJ_DIR}/term_colour.o: ${SRC_DIR}/term_colour.h ${SRC_DIR}/term_colour.c
	${CC} ${CFLAGS} ${SRC_DIR}/term_colour.c -c -o ${OBJ_DIR}/term_colour.o

${OBJ_DIR}/alias.o: ${SRC_DIR}/alias.h ${SRC_DIR}/alias.c
	${CC} ${CFLAGS} ${SRC_DIR}/alias.c -c -o ${OBJ_DIR}/alias.o

$(OBJ_DIR)/view_main.o: $(SRC_DIR)/view/view_main.h $(SRC_DIR)/view/view_main.c
	$(CC) $(CFLAGS) $(SRC_DIR)/view/view_main.c -c -o $(OBJ_DIR)/view_main.o

clean:
	rm -f ${OBJS} ${BINS}

