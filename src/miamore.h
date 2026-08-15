#ifndef MIAMORE_H
#define MIAMORE_H

// MIAMORE : types
typedef enum {
  hidden,
  visible,
} cursor;

typedef unsigned int seconds;

// MIAMORE : Functions
void clear_window(void);
void restore_window(void);

// MISC : Utilities
void wait_for(seconds wait_time);
void manage_cursor(cursor visible);

#endif // MIAMORE_H
