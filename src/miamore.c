#include "miamore.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
// #include <string.h>

// | 24-bit Foreground | \033[38;2;<r>;<g>;<b>m  | Truecolor RGB support |
// | ----------------- | ----------------------- | ----------------------|
// | 24-bit Background | \033[48;2;<r>;<g>;<b>m  | Truecolor RGB support |

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

void wait_for(seconds wait_time) {
  unsigned int retTime = time(0) + wait_time;
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
