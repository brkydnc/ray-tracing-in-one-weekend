#include "ray.h"

vec3 point_at(const Ray *ray, double t) {
  return vec3_add(ray->origin, vec3_mul(ray->direction, t));
};
