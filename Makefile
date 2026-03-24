.EXPORT_ALL_VARIABLES:
TMPDIR ?= /tmp

CC ?= gcc
CFLAGS = -Wall -Wextra -Iinclude
AR = ar
ARFLAGS = rcs

SRC = $(wildcard src/*.c src/fonts/*.c)
OBJ = $(SRC:.c=.o)

LIB = libtuil.a

APP_SRC ?= main.c
APP_BIN ?= main

PREFIX ?= /usr/local
INSTALL_INC = $(PREFIX)/include
INSTALL_LIB = $(PREFIX)/lib

all: $(LIB) app
build: all

$(LIB): $(OBJ)
	TMPDIR=/tmp $(AR) $(ARFLAGS) $@ $^
	@echo "=> Static library compiled to $@"

app: $(LIB)
	@if [ -f "$(APP_SRC)" ]; then \
		TMPDIR=/tmp $(CC) $(CFLAGS) $(APP_SRC) -L. -ltuil -o $(APP_BIN); \
		echo "=> App compiled to $(APP_BIN) (run with ./$(APP_BIN))"; \
	fi

install: $(LIB)
	mkdir -p $(INSTALL_INC) $(INSTALL_LIB)
	cp include/tuil.h include/tuil_fonts.h $(INSTALL_INC)/
	cp $(LIB) $(INSTALL_LIB)/
	@echo "=> TUIL installed globally! You can now use #include <tuil.h> and compile with -ltuil"

uninstall:
	rm -f $(INSTALL_INC)/tuil.h $(INSTALL_INC)/tuil_fonts.h
	rm -f $(INSTALL_LIB)/$(LIB)
	@echo "=> TUIL uninstalled"

clean:
	rm -f $(OBJ) $(LIB) $(APP_BIN)

.PHONY: all build app install uninstall clean
