CC=gcc
CFLAGS=-I
DEPS=2048.c commonFuncts.c genentic.c main.c neuralNet.c 

2048: $(DEPS) 
	$(CC) $(DEPS) -o 2048 -lm
