#ifndef MIAMORE_H
#define MIAMORE_H

// MIAMORE : types
typedef enum {
  hidden,
  visible,
} cursor;

// MIAMORE : Functions
void create_window();
void restore_window(void);

// MISC : Utilities
void wait_for(unsigned int seconds);
void manange_cursor(cursor visible);

#endif // MIAMORE_H
