#   miamore - A terminal user interface library
#   Copyright (C) 2026 Ametrine Foundation
#
#   SPDX-License-Identifier: LGPL-3.0-or-later
#
#   This library is free software; you can redistribute it and/or modify it
#   under the terms of the GNU Lesser General Public License as published
#   by the Free Software Foundation; either version 3 of the License, or
#   any later version.
#
#   This library is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#   GNU Lesser General Public License for more details.
#
#   You should have received a copy of the GNU Lesser General Public License
#   along with this library. If not, see <https://www.gnu.org/licenses/>.
#

# --- Compilers & Flags ---
CC        := clang
CFLAGS    := -Wall -Wextra -O2 -fPIC
AR        := ar
ARFLAGS   := rcs
LDFLAGS   := -lm

# --- Versioning ---
VERSION   := 1.0.0
SOVERSION := 1

# --- Install Paths ---
PREFIX      ?= /usr/local
EXEC_PREFIX ?= $(PREFIX)
LIB_DIR     ?= $(EXEC_PREFIX)/lib
INCLUDE_DIR ?= $(PREFIX)/include
DATAROOTDIR ?= $(PREFIX)/share
LICENSE_DIR ?= $(DATAROOTDIR)/licenses/miamore

INSTALL         := install
INSTALL_PROGRAM := $(INSTALL) -m 755
INSTALL_DATA    := $(INSTALL) -m 644

# --- Source & Object Layout ---
LIB_SRC       := src
OBJ_DIR       := obj
LIB_SRC_FILES := $(LIB_SRC)/miamore.c $(LIB_SRC)/misc.c $(LIB_SRC)/request.c $(LIB_SRC)/framebuffer.c

# Maps src/foo.c to obj/foo.o
LIB_OBJS      := $(patsubst $(LIB_SRC)/%.c,$(OBJ_DIR)/%.o,$(LIB_SRC_FILES))
LIB_HEADER    := $(LIB_SRC)/miamore.h

# --- Output Artifacts ---
STATIC_OUT    := libmiamore.a
REAL_SO_OUT   := libmiamore.so.$(VERSION)
SO_NAME       := libmiamore.so.$(SOVERSION)
DYNAMIC_OUT   := libmiamore.so

# --- Example Layout ---
EXAMPLE_SRC    := examples
EXAMPLE_FILE   := $(EXAMPLE_SRC)/example.c
EXAMPLE_TARGET := example

# --- Targets ---
.PHONY: all dynamic install uninstall example clean

all: $(STATIC_OUT)

# --- Ensure obj/ Directory Exists ---
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# --- Pattern Rule: Compiles src/%.c into obj/%.o ---
$(OBJ_DIR)/%.o: $(LIB_SRC)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(LIB_SRC) -c $< -o $@

# --- Build Static Library ---
$(STATIC_OUT): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^

# --- Build Dynamic Library ---
dynamic: $(REAL_SO_OUT)

$(REAL_SO_OUT): $(LIB_OBJS)
	$(CC) -shared -Wl,-soname,$(SO_NAME) -o $@ $^ $(LDFLAGS)
	ln -sf $(REAL_SO_OUT) $(SO_NAME)
	ln -sf $(SO_NAME) $(DYNAMIC_OUT)

# --- Make C Example ---
example: all $(EXAMPLE_FILE)
	$(CC) $(CFLAGS) -I$(LIB_SRC) $(EXAMPLE_FILE) $(STATIC_OUT) $(LDFLAGS) -o $(EXAMPLE_TARGET)

# --- Install ---
install: all
	# Directories
	$(INSTALL) -d $(DESTDIR)$(LIB_DIR)
	$(INSTALL) -d $(DESTDIR)$(INCLUDE_DIR)
	$(INSTALL) -d $(DESTDIR)$(LICENSE_DIR)

	# Static library
	$(INSTALL_DATA) $(STATIC_OUT) $(DESTDIR)$(LIB_DIR)/$(STATIC_OUT)

	# Dynamic library (if built)
	if [ -f $(REAL_SO_OUT) ]; then \
		$(INSTALL_PROGRAM) $(REAL_SO_OUT) $(DESTDIR)$(LIB_DIR)/$(REAL_SO_OUT); \
		ln -sf $(REAL_SO_OUT) $(DESTDIR)$(LIB_DIR)/$(SO_NAME); \
		ln -sf $(SO_NAME) $(DESTDIR)$(LIB_DIR)/$(DYNAMIC_OUT); \
	fi

	# Headers
	$(INSTALL_DATA) $(LIB_HEADER) $(DESTDIR)$(INCLUDE_DIR)/miamore.h

	# LGPLv3 License Files
	if [ -f LICENSE ]; then $(INSTALL_DATA) LICENSE $(DESTDIR)$(LICENSE_DIR)/LICENSE; fi
	if [ -f LICENSE.LESSER ]; then $(INSTALL_DATA) LICENSE.LESSER $(DESTDIR)$(LICENSE_DIR)/LICENSE.LESSER; fi

# --- Uninstall ---
uninstall:
	rm -f $(DESTDIR)$(LIB_DIR)/$(STATIC_OUT)
	rm -f $(DESTDIR)$(LIB_DIR)/libmiamore.so*
	rm -f $(DESTDIR)$(INCLUDE_DIR)/miamore.h
	rm -rf $(DESTDIR)$(LICENSE_DIR)

# --- Clean ---
clean:
	rm -rf $(OBJ_DIR)
	rm -f $(STATIC_OUT) $(REAL_SO_OUT) $(SO_NAME) $(DYNAMIC_OUT) $(EXAMPLE_TARGET)
