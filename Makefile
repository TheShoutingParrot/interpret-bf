OBJ = main.o util.o
CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra
H_FILES = interpret-bf.h
PREFIX = /usr/local

all: options clean interpret-bf

options:
	@echo "interpret-bf make options:"
	@printf "CC\t= $(CC)\n"
	@printf "CFLAGS\t= $(CFLAGS)\n"
	@printf "PREFIX\t= $(PREFIX)\n\n"

interpret-bf: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c $(H_FILES)
	$(CC) -c $(CFLAGS) $<

install: clean all
	mkdir -p $(PREFIX)/bin
	cp -f interpret-bf $(PREFIX)/bin
	chmod 755 $(PREFIX)/bin/interpret-bf

uninstall:
	rm -f $(PREFIX)/bin/interpret-bf

clean:
	rm -rf interpret-bf $(OBJ)

.PHONY: all options interpret-bf clean install uninstall
