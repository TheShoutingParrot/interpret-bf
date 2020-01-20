OBJ = main.o util.o
CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra
H_FILES = interpret-bf.h
PREFIX = /usr/local

all: interpret-bf

interpret-bf: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c $(H_FILES)
	$(CC) -c $(CFLAGS) $<

install: all
	mkdir -p $(PREFIX)/bin
	cp -f interpret-bf $(PREFIX)/bin
	chmod 755 $(PREFIX)/bin/interpret-bf

uninstall:
	rm -f $(PREFIX)/bin/interpret-bf

clean:
	rm -rf interpret-bf *.o

.PHONY: all interpret-bf clean install uninstall
