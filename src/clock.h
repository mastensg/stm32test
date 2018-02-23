#ifndef CLOCK_H
#define CLOCK_H

#ifdef __cplusplus
extern "C" {
#endif

static const int width = 128;
static const int height = 64;

void clock_init();
void clock_draw(uint8_t *fb, float t);

#ifdef __cplusplus
}
#endif

#endif  // CLOCK_H
