#include "global.h"
#include <stdio.h>

void draw_text(const char *text) {
  check_init();
  fflush(stdout);

  snprintf(temp_buf, sizeof(temp_buf), "%s", text);

  buf_append(fb, temp_buf, sizeof(temp_buf));
  render_frame(fb);
}
