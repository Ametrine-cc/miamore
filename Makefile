# miamore - A terminal user interface library
# Copyright (C) 2026 Ametrine Foundation
#
# SPDX-License-Identifier: LGPL-3.0-or-later
#
# This library is free software; you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published
# by the Free Software Foundation; either version 3 of the License, or
# any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this library. If not, see <https://www.gnu.org/licenses/>.

# --- Compilers & Flags ---
CC       ?= clang
CFLAGS   ?= -Wall -Wextra -O2 -fPIC
CPPFLAGS ?= -I$(LIB_SRC)
AR       ?= ar
ARFLAGS  ?= rcs
LDFLAGS  ?= -lm
CARGO    ?= cargo

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
RS_TARGET     := target
LIB_SRC       := src
OBJ_DIR       := obj
BUILD_DIR     := build

LIB_SRC_FILES := $(LIB_SRC)/miamore.c \
                 $(LIB_SRC)/request.c \
                 $(LIB_SRC)/framebuffer.c \
                 $(LIB_SRC)/draw.c \
                 $(LIB_SRC)/color.c \
                 $(LIB_SRC)/animate.c

# Maps src/foo.c to obj/foo.o
LIB_OBJS      := $(patsubst $(LIB_SRC)/%.c,$(OBJ_DIR)/%.o,$(LIB_SRC_FILES))
LIB_HEADER    := $(LIB_SRC)/miamore.h

# --- Output File Names & Relative Paths ---
LIB_NAME      := libmiamore
STATIC_LIB    := $(LIB_NAME).a
SO_LIB        := $(LIB_NAME).so
SO_REAL       := $(LIB_NAME).so.$(VERSION)
SO_SONAME     := $(LIB_NAME).so.$(SOVERSION)

STATIC_OUT    := $(BUILD_DIR)/$(STATIC_LIB)
REAL_SO_OUT   := $(BUILD_DIR)/$(SO_REAL)
SO_NAME_OUT   := $(BUILD_DIR)/$(SO_SONAME)
DYNAMIC_OUT   := $(BUILD_DIR)/$(SO_LIB)

# --- Example Layout ---
EXAMPLE_SRC    := examples
EXAMPLE_FILE   := $(EXAMPLE_SRC)/example.c
EXAMPLE_TARGET := example

# --- Targets ---
.PHONY: all static dynamic install uninstall example rust-test rust-build clean

all: static dynamic rust-build

rust-test: $(STATIC_OUT)
	$(CARGO) test -- --nocapture

rust-build: $(STATIC_OUT)
	$(CARGO) build --release

# --- Directory Creation ---
$(OBJ_DIR) $(BUILD_DIR):
	mkdir -p $@

# --- Pattern Rule: Compiles src/%.c into obj/%.o ---
$(OBJ_DIR)/%.o: $(LIB_SRC)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# --- Build Static Library ---
static: $(STATIC_OUT)

$(STATIC_OUT): $(LIB_OBJS) | $(BUILD_DIR)
	$(AR) $(ARFLAGS) $@ $^

# --- Build Dynamic Library ---
dynamic: $(REAL_SO_OUT)

$(REAL_SO_OUT): $(LIB_OBJS) | $(BUILD_DIR)
	$(CC) -shared -Wl,-soname,$(SO_SONAME) -o $@ $^ $(LDFLAGS)
	ln -sf $(SO_REAL) $(SO_NAME_OUT)
	ln -sf $(SO_SONAME) $(DYNAMIC_OUT)

# --- Make C Example ---
example: $(EXAMPLE_FILE) $(STATIC_OUT)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(EXAMPLE_FILE) $(STATIC_OUT) $(LDFLAGS) -o $(EXAMPLE_TARGET)

# --- Install ---
install: all
	# Directories
	$(INSTALL) -d $(DESTDIR)$(LIB_DIR)
	$(INSTALL) -d $(DESTDIR)$(INCLUDE_DIR)
	$(INSTALL) -d $(DESTDIR)$(LICENSE_DIR)

	# Static library
	$(INSTALL_DATA) $(STATIC_OUT) $(DESTDIR)$(LIB_DIR)/$(STATIC_LIB)

	# Dynamic library
	if [ -f $(REAL_SO_OUT) ]; then \
		$(INSTALL_PROGRAM) $(REAL_SO_OUT) $(DESTDIR)$(LIB_DIR)/$(SO_REAL); \
		ln -sf $(SO_REAL) $(DESTDIR)$(LIB_DIR)/$(SO_SONAME); \
		ln -sf $(SO_SONAME) $(DESTDIR)$(LIB_DIR)/$(SO_LIB); \
	fi

	# Headers
	$(INSTALL_DATA) $(LIB_HEADER) $(DESTDIR)$(INCLUDE_DIR)/miamore.h

	# LGPLv3 License Files
	if [ -f LICENSE ]; then $(INSTALL_DATA) LICENSE $(DESTDIR)$(LICENSE_DIR)/LICENSE; fi
	if [ -f LICENSE.LESSER ]; then $(INSTALL_DATA) LICENSE.LESSER $(DESTDIR)$(LICENSE_DIR)/LICENSE.LESSER; fi

# --- Uninstall ---
uninstall:
	rm -f $(DESTDIR)$(LIB_DIR)/$(STATIC_LIB)
	rm -f $(DESTDIR)$(LIB_DIR)/$(LIB_NAME).so*
	rm -f $(DESTDIR)$(INCLUDE_DIR)/miamore.h
	rm -rf $(DESTDIR)$(LICENSE_DIR)

# --- Clean ---
clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR) $(EXAMPLE_TARGET)
	$(CARGO) clean 2>/dev/null || rm -rf $(RS_TARGET)
