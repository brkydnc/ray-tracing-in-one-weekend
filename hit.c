#include <stdbool.h>
#include <math.h>
#include "sphere.h"
#include "hit.h"

void set_face_normal(HitRecord *record, Ray ray, vec3 outward_normal) {
  record->front_face = vec3_dot(ray.direction, outward_normal) < 0;
  record->normal = record->front_face ? outward_normal : vec3_mul(outward_normal, -1.0);
}

bool ray_hits_sphere(Sphere sphere, Ray ray, double t_min, double t_max, HitRecord *record) {
  vec3 ctr = vec3_sub(ray.origin, sphere.position); // center to ray
  double a = vec3_dot(ray.direction, ray.direction);
  double half_b = vec3_dot(ray.direction, ctr);
  double c = vec3_dot(ctr, ctr) - sphere.radius * sphere.radius;

  double discriminant = half_b*half_b - a*c;
  if (discriminant < 0) return false;
  double sqrtd = sqrt(discriminant);

  double root = (-half_b - sqrtd) / a; 
  if (root < t_min || t_max < root) {
    root = (-half_b + sqrtd) / a; 
    if (root < t_min || t_max < root) return false;
  }

  record->t = root;
  record->point = point_at(ray, root);
  vec3 outward_normal = vec3_div(vec3_sub(record->point, sphere.position), sphere.radius);
  set_face_normal(record, ray, outward_normal);

  return true;
}
