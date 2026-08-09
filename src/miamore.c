#include "miamore.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
// #include <string.h>

static const char *MANAGE_CURSOR_STR[] = {
    [hidden] = "\033[?25l",
    [visible] = "\033[?25h",
};

// miamore misc functions
void manage_cursor(cursor shown) {
  if (shown == hidden) {
    const char *hide = MANAGE_CURSOR_STR[shown];
    printf("%s", hide);
  } else if (shown == visible) {
    const char *hide = MANAGE_CURSOR_STR[shown];
    printf("%s", hide);
  }

  fflush(stdout);
}

void wait_for(unsigned int seconds) {
  unsigned int retTime = time(0) + seconds;
  while (time(0) < retTime)
    ;
}

// miamore functions
void restore_window(void) {
  printf("\033[1;1H\033[0m\n");
  fflush(stdout);
}

void clear_window(void) {
  printf("\033[2J");
  fflush(stdout);
}

void create_window() {
  printf("%s\n", __FUNCTION__);
  // restore_window();
  printf("\033[20;20H\n");
  manage_cursor(hidden);

  wait_for(2);
  clear_window();

  manage_cursor(visible);

  restore_window();
}
