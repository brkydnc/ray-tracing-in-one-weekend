#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct {
  vec3 origin;
  vec3 direction;
} Ray;

vec3 point_at(Ray ray, double t);

#endif
