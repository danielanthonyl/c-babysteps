INCLUDES= -I ./include
FLAGS= -g
all:
	gcc ${FLAGS} ${INCLUDES} ./src/main.c -L ./lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o ./bin/main