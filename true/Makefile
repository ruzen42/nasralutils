SRC=main.c
CC=cc
CFLAGS=-O2 -o true -nostdlib -static

all:
	$(CC)  $(CFLAGS) $(SRC)

clean:
	rm true 
install:\n\tinstall -m777 true /usr/local/bin/
