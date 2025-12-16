SRC=main.c
CC=cc
CFLAGS=-O0 -o kill-it -lX11 -lm 

all:
	$(CC)  $(CFLAGS) $(SRC)

clean:
	rm kill-it 

install: 
	install -m 777 -T kill-it /usr/local/bin/kill-it
