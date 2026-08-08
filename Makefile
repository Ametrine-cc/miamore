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

# --- Targets ---
.PHONY: all install uninstall example clean

all: $(LIB_OUT) $(TARGET)

# --- Compile library object ---
$(LIB_OBJ): $(LIB_SRC_FILES)
	$(CXX) $(CXXFLAGS) -I$(LIB_SRC) -c $< -o $@

$(LIB_OUT): $(LIB_OBJ)
	$(AR) $(ARFLAGS) $@ $^

# --- Make C example ---
c_example: all
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
