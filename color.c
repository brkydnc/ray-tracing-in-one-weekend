#include <stdio.h>
#include "color.h"
#include "sphere.h"
#include "util.h"

const Color WHITE = {255.0, 255.0, 255.0};
const Color SKY_BLUE = {128.0, 179.0, 255.0};

Color color_from(double r, double g, double b) {
  Color color = {r, g, b};
  return color;
}

void write_color(FILE *out, Color color, int samples_per_pixel) {
  unsigned red = (unsigned) color.x;
  unsigned green = (unsigned) color.y;
  unsigned blue = (unsigned)  color.z;

  double scale = 1.0 / samples_per_pixel;
  red *= scale;
  green *= scale;
  blue *= scale;

  red = clamp(red, 0.0, 255.0);
  green = clamp(green, 0.0, 255.0);
  blue = clamp(blue, 0.0, 255.0);

  fprintf(out, "%u %u %u\n", red, green, blue);
}
