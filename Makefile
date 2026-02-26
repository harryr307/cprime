CC=gcc
CCLD=gcc
PROJNM=cprime
OBJS=main.o
CCA=-c -Wall
CCLDA=-std=gnu99 -o $(PROJNM)

$(PROJNM): $(OBJS)
	$(CCLD) $(CCLDA) $(OBJS)

main.o: main.c
	$(CC) $(CCA) main.c -o main.o
