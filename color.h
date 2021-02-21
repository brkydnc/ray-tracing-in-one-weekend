#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>
#include "vec3.h"
#include "ray.h"

typedef vec3 Color;

extern const Color WHITE;
extern const Color SKY_BLUE;

Color color_from(double r, double g, double b);
Color ray_color(Ray ray);
void write_color(FILE *out, Color color);

#endif
