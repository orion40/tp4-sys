CC=gcc
CFLAGS=-Wall -ggdb  -O2
LDLIBS=-lpthread
LIB=
IN=philosophes.c fourchettes.c
OUT=philosophes

all:
	$(CC) $(CFLAGS) $(IN) -o $(OUT) $(LDLIBS)

clean:
	$(RM) exo3 *.o
