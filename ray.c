#include "ray.h"

Ray ray_from(vec3 origin, vec3 direction) {
  Ray ray = { origin, direction };
  return ray;
}

vec3 point_at(const Ray *ray, double t) {
  return vec3_add(ray->origin, vec3_mul(ray->direction, t));
}
