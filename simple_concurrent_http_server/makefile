CC=gcc
CCFLAGS=-Wall -Wextra
interface.o:interface.c
	$(CC) $(CCFLAGS) -g -c $< -o $@
server:server.c interface.o
	$(CC) $(CCFLAGS) -g $^ -o $@
