#include "miamore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void buf_append(FrameBuffer *fb, const char *str, size_t len) {
  if (!fb)
    return;

  if (fb->len + len > fb->capacity) {
    size_t new_cap = (fb->capacity == 0) ? 1024 : (fb->len + len) * 2;
    char *new_data = realloc(fb->data, new_cap);
    if (!new_data)
      return;

    fb->data = new_data;
    fb->capacity = new_cap;
  }
  memcpy(fb->data + fb->len, str, len);
  fb->len += len;
}

void render_frame(FrameBuffer *fb) {
  if (!fb || fb->len == 0)
    return;

  write(STDOUT_FILENO, fb->data, fb->len);
  fb->len = 0;
}
