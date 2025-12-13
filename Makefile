SRC=main.c
CC=cc
CFLAGS=-O2 -o yes

all:
	$(CC)  $(CFLAGS) $(SRC)

clean:
	rm yes
