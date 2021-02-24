#include <stdio.h>
#include <math.h>
#include "color.h"
#include "sphere.h"
#include "util.h"

const Color WHITE = {1.0, 1.0, 1.0};
const Color SKY_BLUE = {0.5, 0.7, 1.0};

Color color_from(double r, double g, double b) {
  Color color = {r, g, b};
  return color;
}

void write_color(FILE *out, const Color *color, int samples_per_pixel) {
  double red = color->x;
  double green = color->y;
  double blue = color->z;

  double scale = 1.0 / samples_per_pixel;
  // gamma correction & scale to average color
  red = sqrt(red * scale);
  green = sqrt(green * scale);
  blue = sqrt(blue * scale);

  red = clamp(red, 0.0, 1.0) * 255;
  green = clamp(green, 0.0, 1.0) * 255;
  blue = clamp(blue, 0.0, 1.0) * 255;

  fprintf(out, "%i %i %i\n", (int) red, (int) green, (int) blue);
}
