#include "display.h"
#include <cstdio>
#include <cassert>
#include <memory>	// had to change from <cmemory> to compile

#define W 16
#define H  9
static unsigned short frame_buffer[W*H];

Display::Display()
{
  memset(frame_buffer, 0, sizeof(frame_buffer));
}

// This displays the color ramp
Display::~Display()
{
  unsigned short *pix = frame_buffer;
  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++) {
      if (x > 0) {
        printf(" ");
      }
      printf("%04X", *pix++);
    }
    printf("\n");
  }
}

bool Display::connect(const char *display_name)
{
  return true;
}

void Display::get_size(int &width, int &height)
{
  width = W;
  height = H;
}

void Display::draw_raster(int x, int y,
    const unsigned short *pixels, int width)
{
  memcpy(&frame_buffer[y*W+x], pixels, width*sizeof(unsigned short)); //so copy is from BEGINNING of pixels to xth column of yth row
}
