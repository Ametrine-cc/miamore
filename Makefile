# miamore: The C tui library
# Copyright (C) 2026  Ametrine Foundation

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.

# You should have received a copy of the GNU Affero General Public License
# along with this program.   If not, see <https://www.gnu.org/licenses/>

# --- Compilers ---
CC        := clang
CFLAGS    := -Wall -Wextra -O2
AR        := ar
ARFLAGS   := rcs

# --- Source Layout ---
LIB_SRC       := src
LIB_SRC_FILES := $(LIB_SRC)/miamore.c $(LIB_SRC)/framebuffer.c $(LIB_SRC)/draw.c $(LIB_SRC)/misc.c $(LIB_SRC)/color.c
LIB_OBJS      := $(LIB_SRC_FILES:.c=.o)
LIB_HEADER    := $(LIB_SRC)/miamore.h
LIB_OUT       := libmiamore.a

# --- Example Layout ---
EXAMPLE_SRC    := examples
EXAMPLE_FILE   := $(EXAMPLE_SRC)/example.c
EXAMPLE_TARGET := example

# --- Install paths ---
PREFIX      := /usr/local
LIB_DIR     := $(PREFIX)/lib
INCLUDE_DIR := $(PREFIX)/include

LDFLAGS     := -lm

# --- Targets ---
.PHONY: all install uninstall example clean

all: $(LIB_OUT)

# --- Pattern rule for compiling object files ---
$(LIB_SRC)/%.o: $(LIB_SRC)/%.c
	$(CC) $(CFLAGS) -I$(LIB_SRC) -c $< -o $@

# --- Build Static Library ---
$(LIB_OUT): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^

# --- Make C example ---
example: all $(EXAMPLE_FILE)
	$(CC) $(CFLAGS) -I$(LIB_SRC) $(EXAMPLE_FILE) $(LIB_OUT) $(LDFLAGS) -o $(EXAMPLE_TARGET)

# --- Install ---
install: all
	install -Dm644 $(LIB_OUT)    $(DESTDIR)$(LIB_DIR)/$(LIB_OUT)
	install -Dm644 $(LIB_HEADER) $(DESTDIR)$(INCLUDE_DIR)/miamore.h

# --- Uninstall ---
uninstall:
	rm -f $(DESTDIR)$(LIB_DIR)/$(LIB_OUT)
	rm -f $(DESTDIR)$(INCLUDE_DIR)/miamore.h

# --- Clean ---
clean:
	rm -f $(LIB_OBJS) $(LIB_OUT) $(EXAMPLE_TARGET)
