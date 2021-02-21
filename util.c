#include <stdlib.h>
#include <math.h>
#include "util.h"

double clamp(double value, double min, double max) {
  if (value > max) return max;
  if (value < min) return min;
  return value;
}

double degrees_to_radians(double degrees) {
  return degrees * M_PI / 180.0;
}

double random_double() {
  return rand() / (RAND_MAX + 1.0);
}

double random_double_in(double min, double max) {
  return min + (max - min) * random_double();
}
