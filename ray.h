#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct {
  vec3 origin;
  vec3 direction;
} Ray;

Ray ray_from(vec3 origin, vec3 direction);
vec3 point_at(const Ray *ray, double t);

#endif
