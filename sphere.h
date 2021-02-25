#ifndef SPHERE_H
#define SPHERE_H
#include "vec3.h"
#include "material.h"

typedef struct {
  vec3 position;
  double radius;
  Material material;
} Sphere;

Sphere sphere_from(vec3 position, double radius, Material material);

#endif
