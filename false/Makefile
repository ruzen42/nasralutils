SRC=main.c
CC=cc
CFLAGS=-O2 -o false -nostdlib -static

all:
	$(CC)  $(CFLAGS) $(SRC)

clean:
	rm false 
install:\n\tinstall -m777 false /usr/local/bin/
