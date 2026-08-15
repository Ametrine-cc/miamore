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

CXX       := clang
CXXFLAGS  := -Wall -Wextra -O2
AR        := ar
ARFLAGS   := rcs

# --- Source Layout ---
LIB_SRC       := src
LIB_SRC_FILES := $(LIB_SRC)/miamore.c
LIB_OBJ       := $(LIB_SRC)/miamore.o
LIB_HEADER    := $(LIB_SRC)/miamore.h
LIB_OUT       := libmiamore.a

# LICENSE := LICENSE

# --- Exmaple Layout ---
EXAMPLE_SRC    := examples
EXAMPLE_FILE   := $(EXAMPLE_SRC)/example.c
EXAMPLE_TARGET := example

# --- Install paths ---
PREFIX      := /usr/local
LIB_DIR     := $(PREFIX)/lib
INCLUDE_DIR := $(PREFIX)/include

INCLUDE     := -lm

# --- Targets ---
.PHONY: all install uninstall example clean

all: $(LIB_OUT) $(TARGET)

# --- Compile library object ---
$(LIB_OBJ): $(LIB_SRC_FILES)
	$(CXX) $(CXXFLAGS) -I$(LIB_SRC) $(INCLUDE) -c $< -o $@

$(LIB_OUT): $(LIB_OBJ)
	$(AR) $(ARFLAGS) $@ $^

# --- Make C example ---
example: all
	$(CXX) $(CXXFLAGS) $(EXAMPLE_FILE) $(LIB_OUT) -o $(EXAMPLE_TARGET)

# --- Install ---
install: all
	install -Dm644 $(LIB_OUT)    $(DESTDIR)$(LIB_DIR)/$(LIB_OUT)
	install -Dm644 $(LIB_HEADER) $(DESTDIR)$(INCLUDE_DIR)/miamore.h

# --- Uninstall ---
uninstall:
	rm -r $(DESTDIR)$(LIB_DIR)/$(LIB_OUT)
	rm -r $(DESTDIR)$(INCLUDE_DIR)/miamore.h

clean:
	rm -r $(LIB_OBJ) $(LIB_OUT) $(EXAMPLE_TARGET)
