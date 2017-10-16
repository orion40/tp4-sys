CC=gcc
CFLAGS=-Wall -ggdb  -O2
LDLIBS=-lpthread
LIB=
IN=exo3.c fourchettes.c
OUT=exo3


all:
	$(CC) $(CFLAGS) $(IN) -o $(OUT) $(LDLIBS)

clean:
	$(RM) exo3 *.o
