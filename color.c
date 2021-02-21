#include <stdio.h>
#include "color.h"
#include "sphere.h"

const Color WHITE = {255.0, 255.0, 255.0};
const Color SKY_BLUE = {128.0, 179.0, 255.0};

Color color_from(double r, double g, double b) {
  Color color = {r, g, b};
  return color;
}

void write_color(FILE *out, Color color) {
  unsigned red = (unsigned) color.x;
  unsigned green = (unsigned) color.y;
  unsigned blue = (unsigned)  color.z;
  fprintf(out, "%u %u %u\n", red, green, blue);
}
